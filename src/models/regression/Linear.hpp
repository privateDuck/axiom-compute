#pragma once
#include "../interface/IModel.hpp"
#include <definitions.hpp>
#include <torch/torch.h>
#include <torch/nn.h> 
#include <torch/data.h>

class LinearRegressorImpl : torch::nn::Module {
public:
	LinearRegressorImpl() = default;
	~LinearRegressorImpl() override = default;

	LinearRegressorImpl(RegressionLoss loss, double l1_regularization, double l2_regularization);

	// Inherited via IModel
	void fit(const Matrix& X, const Vector& y) override;
	InferenceResult predict(const Matrix& X) const override;
	void save(std::ostream& out) const override;
	void load(std::istream& in) override;

private:
	virtual torch::Tensor forward(const torch::Tensor& input) {
		return input;
	}

	torch::Tensor l1_loss(const torch::Tensor& w) {
		return  torch::abs(w).sum();
	}

	torch::Tensor l2_loss(const torch::Tensor& w) {
		return  torch::square(w).sum();
	}
};