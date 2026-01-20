#pragma once

#include <memory>
#include <torch/torch.h>
#include <torch/nn.h>
#include <torch/optim.h>
#include "EigenDataset.hpp"


//class LibTorchLogisticBackend : public torch::nn::Module {
//private:
//	torch::nn::Linear linear{ nullptr };
//public:
//	LibTorchLogisticBackend(int64_t input_dim, int64_t output_dim)
//		: linear(register_module("linear", torch::nn::Linear(input_dim, output_dim))) { }
//
//	torch::Tensor forward(const torch::Tensor& x) {
//		return linear->forward(x);
//	}
//};


// Linear model using Libtorch
// Used in both LinearSVC (MultiMarginLoss) and Logistic Regression (CrossEntropyLoss)
class LibTorchLinearBackend : public torch::nn::Module {
private:
	torch::nn::Linear linear{ nullptr };
public:
	LibTorchLinearBackend(int64_t input_dim, int64_t output_dim)
		: linear(register_module("linear", torch::nn::Linear(input_dim, output_dim))) {}

	torch::Tensor forward(const torch::Tensor& x) {
		return linear->forward(x);
	}

};

// RBF SVM model using Libtorch
// Uses random Fourier features to approximate the RBF kernel
class LibTorchRBFSVCBackend : public torch::nn::Module {
private:
	torch::nn::Linear linear{ nullptr };
	torch::Tensor random_weights;
	torch::Tensor random_bias;
	double gamma;
	double dims;
public:
	LibTorchRBFSVCBackend(int64_t input_dim, int64_t output_dim, double gamma, double dims)
		: linear(register_module("linear", torch::nn::Linear(input_dim, output_dim))), gamma(gamma), dims(dims) {
		register_buffer("random_weights", random_weights);
		register_buffer("random_bias", random_bias);
	}

	void generate_random_features(int64_t input_dim) {
		auto options = torch::TensorOptions().dtype(torch::kFloat32);
		random_weights = torch::empty({ input_dim, static_cast<int64_t>(dims) }, options);
		torch::nn::init::normal_(random_weights, 0.0, std::sqrt(2 * gamma));
		random_bias = torch::empty({ static_cast<int64_t>(dims) }, options);
		torch::nn::init::uniform_(random_bias, 0.0, 2 * M_PI);
	}

	torch::Tensor forward(const torch::Tensor& x) {
		// Generate random Fourier features
		auto z = torch::matmul(x, random_weights) + random_bias;
		z = torch::cos(z) * std::sqrt(2.0 / dims);
		return linear->forward(z);
	}
};

// Train a Linear Regression model (Uses LGBFS)
/// dataset: training dataset
/// epochs: number of epochs
/// regularization_type: 0 -> L1, 1 -> L2, 2 -> Elastic Net (L1 + L2)
/// returns: trained model backend
std::unique_ptr<LibTorchLinearBackend> train_libtorch_linreg(
	const EigenColAlignedFloatMat& X,
	const EigenColFloatVec& y,
	int64_t epochs,
	int64_t max_iter,
	size_t regularization_type,
	double l1_regularization,
	double l2_regularization
);


// Train a Logistic Regression model (Uses LGBFS)
/// dataset: training dataset
/// epochs: number of epochs
/// regularization_type: 0 -> L1, 1 -> L2, 2 -> Elastic Net (L1 + L2)
/// returns: trained model backend
std::unique_ptr<LibTorchLinearBackend> train_libtorch_logitreg(
	const EigenColAlignedFloatMat& X,
	const EigenColFloatVec& y,
	int64_t epochs,
	int64_t max_iter,
	size_t regularization_type,
	double l1_regularization,
	double l2_regularization
);


// Train the SVM model
/// dataset: training dataset
/// epochs: number of epochs
/// learning_rate: learning rate for optimizer
/// C: regularization parameter
/// beta: parameter for Huber loss
/// regularization_type: 0 -> L1, 1 -> L2, 2 -> Elastic Net (L1 + L2)
/// returns: trained model backend
std::unique_ptr<LibTorchLinearBackend> train_libtorch_linear_SVM(
	const EigenColAlignedFloatMat& X, 
	const EigenColFloatVec& y,
	int64_t epochs, 
	double learning_rate, 
	double C, 
	double beta, 
	size_t regularization_type
);

// Train the RBF SVM model
/// dataset: training dataset
/// epochs: number of epochs
/// learning_rate: learning rate for optimizer
/// C: regularization parameter
/// beta: parameter for Huber loss
/// regularization_type: 0 -> L1, 1 -> L2, 2 -> Elastic Net (L1 + L2)
/// gamma: RBF kernel parameter
/// dims: number of random Fourier features
/// returns: trained model backend
std::unique_ptr<LibTorchRBFSVCBackend> train_libtorch_rbf_SVM(
	const EigenColAlignedFloatMat& X,
	const EigenColFloatVec& y,
	int64_t epochs,
	double learning_rate,
	double C,
	double beta,
	size_t regularization_type,
	double gamma,
	double dims
);