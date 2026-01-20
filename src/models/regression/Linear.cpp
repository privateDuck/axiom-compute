#include "Linear.hpp"
#include <torch/optim.h>
#include <svm.h>

void fn() {
	svm_problem a;
}

torch::Tensor closure(torch::Tensor x) {
	return x.sum();
}

void LinearRegressorImpl::fit(const Matrix& X, const Vector& y)
{
    torch::optim::LBFGS optimizer(this->parameters());
	torch::Tensor X_t = torch::from_blob((void*)X.data(), { X.rows(), X.cols() }, torch::kFloat64);
	torch::Tensor y_t = torch::from_blob((void*)y.data(), { y.size() , 1 }, torch::kFloat64);

	for (size_t i = 0; i < n_iter; i++)
	{
		optimizer.zero_grad();
		torch::Tensor predictions = this->forward(X_t);
		torch::Tensor loss = torch::mse_loss(predictions, y_t);
		torch::hinge_embedding_loss
		loss.backward();
		optimizer.step([] { return closure; });

	}
}

InferenceResult LinearRegressorImpl::predict(const Matrix& X) const
{
    return InferenceResult();
}

void LinearRegressorImpl::save(std::ostream& out) const
{
}

void LinearRegressorImpl::load(std::istream& in)
{
}
