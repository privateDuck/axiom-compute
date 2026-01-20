#pragma once

#include <memory>
#include <torch/torch.h>
#include <torch/nn.h>
#include <torch/optim.h>
#include "EigenDataset.hpp"
#include "MultivariateNormalDist.hpp"


// Linear Discriminant Analysis model using Libtorch
class LibTorchDirectLDABackend : public torch::nn::Module {
private:
	torch::Tensor means, priors, classes, precision_tensor, log_det_cov;

public:
	LibTorchDirectLDABackend() {
		register_buffer("means", means);
		register_buffer("priors", priors);
		register_buffer("classes", classes);
		register_buffer("precision_tensor", precision_tensor);
		register_buffer("log_det_cov", log_det_cov);
	}

	void fit(const std::vector<EigenRowAlignedFloatMat>& Xs, const std::vector<float>& all_classes, const float X_rows, const float X_cols, double reg_param) {
		const int64_t n_classes = all_classes.size();
		classes = torch::from_blob((void*)all_classes.data(), { n_classes }, torch::kFloat32).clone();
		priors = torch::zeros({ n_classes }, torch::kFloat32); // dims { n }
		auto shared_cov = torch::zeros({ (int64_t)X_cols, (int64_t)X_cols }, torch::kFloat32); // dims { f, f }
		means = torch::zeros({ n_classes, (int64_t)X_cols }, torch::kFloat32); // { n, f }

		int32_t counter = 0;
		for (const auto& data : Xs) {
			const float XcSize = static_cast<float>(data.rows());
			torch::Tensor X = torch::from_blob((void*)data.data(), { (int64_t)data.rows(), (int64_t)data.cols() }, torch::kFloat32);
			
			float prior = XcSize / X_rows;
			priors[counter] = std::log(prior);
			const auto mean = torch::mean(X, 0);
			means[counter] = mean;

			const auto centered = X - mean;
			shared_cov.addmm_(centered.t(), centered);

			counter++;
		}

		shared_cov /= (X_rows - static_cast<float>(n_classes));
		shared_cov.add_(torch::eye(static_cast<int64_t>(X_cols)), reg_param);

		// cholesky shared cov (F, F)
		auto L = torch::linalg_cholesky(shared_cov);

		// (F, F)
		precision_tensor = torch::cholesky_inverse(L);

		log_det_cov = 2 * L.diagonal().log().sum();
	}

	torch::Tensor predict_log_proba(torch::Tensor& X) {
		double dim = X.size(1);
		double log_2pi = std::log(2 * M_PI);
		auto constant_term = -0.5 * (log_det_cov + dim * log_2pi);

		// Term A: x^T * Sigma^-1 * x  (Quadratic Term)
		auto X_P = torch::matmul(X, precision_tensor);
		auto term_x = (X_P * X).sum(1).unsqueeze(1);

		// Term B: mu^T * Sigma^-1 * mu (Class Constant)
		auto term_mu = (torch::matmul(means, precision_tensor) * means).sum(1);
		// Term C: -2 * x^T * Sigma^-1 * mu (Linear Interaction)
		auto term_interaction = -2 * torch::matmul(X_P, means.t());

		auto mahalanobis_sq = term_x + term_mu.unsqueeze(0) + term_interaction;

		// Log Likelihood = Constant - 0.5 * Mahalanobis
		auto log_likelihood = constant_term - 0.5 * mahalanobis_sq;

		return log_likelihood + priors.unsqueeze(0);
	}

	torch::Tensor predict_proba(torch::Tensor& X) {
		auto logits = predict_log_proba(X);
		return torch::softmax(logits, 1);
	}

	torch::Tensor predict(torch::Tensor& X) {
		auto logits = predict_log_proba(X);
		return torch::argmax(logits, 1);
	}

	torch::Tensor forward(torch::Tensor& X) {
		return predict_log_proba(X);
	}
};



// Quadratic Discriminant Analysis model using Libtorch
class LibTorchDirectQDABackend : public torch::nn::Module {
private:
	torch::Tensor means, precision_tensors, log_det_covs , priors, classes;

public:
	LibTorchDirectQDABackend() {
		register_buffer("means", means);
		register_buffer("precision_tensors", precision_tensors);
		register_buffer("log_det_covs", log_det_covs);
		register_buffer("priors", priors);
		register_buffer("classes", classes);
	}

	void fit(const std::vector<EigenRowAlignedFloatMat>& Xs, const std::vector<float>& all_classes, const float X_rows, const float X_cols, double reg_param) {
		int64_t n_classes = static_cast<int64_t>(all_classes.size());
		classes = torch::from_blob((void*)all_classes.data(), { n_classes }, torch::kFloat32).clone();
		priors = torch::zeros({ n_classes }, torch::kFloat32); // dims { n }
		auto covs_tensor = torch::zeros({ n_classes, (int64_t)X_cols, (int64_t)X_cols }, torch::kFloat32);
		means = torch::zeros({ n_classes, (int64_t)X_cols }, torch::kFloat32); // { n, f }

		int32_t counter = 0;
		for (const auto& data : Xs) {
			const float XcSize = static_cast<float>(data.rows());
			torch::Tensor X = torch::from_blob((void*)data.data(), { (int64_t)data.rows(), (int64_t)data.cols() }, torch::kFloat32);

			float prior = XcSize / X_rows;
			priors[counter] = std::log(prior);
			const auto mean = torch::mean(X, 0);
			means[counter] = mean;

			const auto centered = X - mean;
			const auto cov = torch::matmul(centered.t(), centered).div_(XcSize - 1.0f);

			cov.add_(torch::eye(static_cast<int64_t>(X_cols)), reg_param);
			covs_tensor[counter] = cov;

			counter++;
		}

		auto L = torch::linalg_cholesky(covs_tensor); // (C, F, F)
		// Inverse covariances
		precision_tensors = torch::cholesky_inverse(L);
		// 2 * sum(log(diag(L)))
		log_det_covs = 2.0 * L.diagonal(0, -2, -1).log().sum(-1);
	}

	torch::Tensor predict_log_proba(torch::Tensor& X) {
		// We broadcast X against Means to get the difference vectors for every class combo
		auto delta = X.unsqueeze(1) - means.unsqueeze(0);

		// Apply Precision Matrix (Mahalanobis Distance)
		// We need: delta^T * Precision * delta

		// Reshape delta for matrix multiplication: (Batch, Classes, 1, Features)
		auto delta_vec = delta.unsqueeze(2);

		// Prepare precisions for broadcasting over batch: (1, Classes, Features, Features)
		auto P_view = precision_tensors.unsqueeze(0);

		// Compute (delta^T * P): 
		auto weighted_delta = torch::matmul(delta_vec, P_view);

		// Compute dot product with delta: (delta^T * P) * delta
		auto mahalanobis = (weighted_delta * delta_vec).sum(-1).squeeze(-1);

		// Compute Log Probability
		// Constant: -0.5 * (Log(Det) + Dim * Log(2Pi))
		double dim = X.size(1);
		double log_2pi = std::log(2 * M_PI);

		// log_det_covs is (Classes), broadcasts to (Batch, Classes)
		auto constants = -0.5 * (log_det_covs.unsqueeze(0) + dim * log_2pi);

		auto log_likelihood = constants - 0.5 * mahalanobis;

		return log_likelihood + priors.unsqueeze(0);
	}

	torch::Tensor predict_proba(torch::Tensor& X) {
		auto logits = predict_log_proba(X);
		return torch::softmax(logits, 1);
	}

	torch::Tensor predict(torch::Tensor& X) {
		auto logits = predict_log_proba(X);
		return torch::argmax(logits, 1);
	}

	torch::Tensor forward(torch::Tensor& X) {
		return predict_log_proba(X);
	}
};



class LibTorchDifferentiableQDABackend : public torch::nn::Module {
private:
	torch::Tensor means, precision_factors, class_log_priors;
	uint64_t cov_mode; // 0 - full, 1 - diag
	int64_t n_classes; 
public:
	LibTorchDifferentiableQDABackend(int64_t n_features, int64_t n_classes, uint64_t cov_mode)
		: cov_mode(cov_mode), n_classes(n_classes) {
		
		if (cov_mode > 1) {
			throw std::runtime_error("Invalid cov_mode for Differentiable QDA. Must be 0 (full) or 1 (diag).");
		}
		means = register_parameter("means", torch::zeros({ n_classes, n_features}));
		
		if (cov_mode == 0) {
			torch::Tensor pf = torch::eye(n_features).unsqueeze(0).repeat({ n_classes, 1, 1 });
			precision_factors = register_parameter("precision_factors", pf);
		}
		else if (cov_mode == 1) {
			torch::Tensor pf = torch::ones({ n_classes, n_features });
			precision_factors = register_parameter("precision_factors", pf);
		}
		class_log_priors = register_parameter("class_log_priors", torch::zeros({ n_classes }));
	}

	torch::Tensor forward(const torch::Tensor& X) {
		// X shape : (Batch, Features)
		
		// Broadcast X and Means to compute Delta
		// X_view: (Batch, 1, Features)
		auto X_view = X.unsqueeze(1);
		// means_view: (1, Classes, Features)
		auto means_view = means.unsqueeze(0);

		// delta: (Batch, Classes, Features)
		auto delta = X_view - means_view;

		torch::Tensor mahalanobis, log_det_precision;

		if (cov_mode == 0 /* cov mode full */) {
			
			// Enforce lower triangular structure on the whole batch of matrices
			// L_tril: (Classes, Features, Features)
			auto L_tril = torch::tril(precision_factors);

			// Reshape for batch matrix multiplication
			// delta: (Batch, Classes, 1, Features)
			auto delta_unsqueezed = delta.unsqueeze(2);

			// L_tril: (1, Classes, Features, Features) - Broadcast over Batch dim
			auto L_tril_view = L_tril.unsqueeze(0);

			// We need: delta * L^T
			// Input: (B, C, 1, F) x (1, C, F, F) -> (B, C, 1, F)
			auto weighted_delta = torch::matmul(delta_unsqueezed, L_tril_view.transpose(-1, -2));

			// Squeeze and sum squares: || delta * L^T ||^2
			mahalanobis = torch::sum(weighted_delta.squeeze(2).pow(2), 2); // (Batch, Classes)

			// Log Determinant
			// diagonal gives (Classes, Features), sum gives (Classes)
			auto diag_elements = torch::diagonal(L_tril, 0, 1, 2);
			log_det_precision = 2.0f * torch::sum(torch::log(torch::abs(diag_elements)), 1);
		}
		else /* cov mode diag */ {

			// precision_factors: (Classes, Features)
			// Broadcast over batch: (1, Classes, Features)
			auto L_view = precision_factors.unsqueeze(0);

			// Element-wise multiplication
			auto weighted_delta = delta * L_view;

			// Sum squares
			mahalanobis = torch::sum(weighted_delta.pow(2), 2); // (Batch, Classes)

			// Log Determinant
			log_det_precision = 2.0f * torch::sum(torch::log(torch::abs(precision_factors)), 1);
		}

		// log_det_precision is (Classes). Broadcast to (Batch, Classes) automatically in subtraction.
		auto log_prob = 0.5f * (log_det_precision.unsqueeze(0) - mahalanobis);

		// Add priors: (Classes) -> Broadcast to (Batch, Classes)
		return log_prob + class_log_priors.unsqueeze(0);
	}

	/*torch::Tensor forward(const torch::Tensor& X) {
		torch::Tensor log_joint_probs_tensor = torch::zeros({ X.size(0), n_classes }, torch::kFloat32);
		for (size_t i = 0; i < n_classes; i++)
		{
			auto mean = means[i];
			torch::Tensor cov_inv;
			torch::Tensor log_det_cov;
			if (cov_mode == 0) {
				auto pf = precision_factors[i];
				cov_inv = torch::matmul(pf.t(), pf);
				log_det_cov = 2.0 * torch::logdet(pf);
			}
			else {
				auto pf = precision_factors[i];
				cov_inv = torch::diag_embed(pf * pf);
				log_det_cov = 2.0 * torch::log(pf).sum();
			}
			auto diff = X - mean;
			auto mahalanobis = torch::sum(diff.unsqueeze(1).matmul(cov_inv) * diff.unsqueeze(2), 2).squeeze();
			torch::Tensor log_prior;
			if (cov_mode == 0) {
				log_prior = torch::zeros({ 1 });
			}
			else {
				log_prior = class_log_priors[i];
			}
			auto log_likelihood = -0.5 * (mahalanobis + log_det_cov + X.size(1) * std::log(2 * M_PI));
			auto log_joint_prob = log_likelihood + log_prior;
			log_joint_probs_tensor.index_put_({ torch::indexing::Slice(), static_cast<int64_t>(i) }, log_joint_prob);
		}
		return log_joint_probs_tensor;
	}*/
};