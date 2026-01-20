#include "LinearRegressor.hpp"

void LinearRegressor::fit(const Matrix& X, const Vector& y)
{
	const auto arma_X = view_as_arma(X);
	const auto arma_y = view_as_arma(y);
	model_.Train(arma_X, arma_y, l2_reg, fit_intercept);
}

InferenceResult LinearRegressor::predict(const Matrix& X) const
{
	Vector predictions(X.rows());
	const auto arma_X = view_as_arma(X);
	auto arma_preds = view_as_arma(predictions);
	model_.Predict(arma_X, arma_preds);

	return predictions;
}

void LinearRegressor::save(std::ostream& out) const
{
}

void LinearRegressor::load(std::istream& in)
{
}

void NearestNeighborRegressor::fit(const Matrix& X, const Vector& y)
{
	//model_ = mlpack::neighbor::KNN()
}

InferenceResult NearestNeighborRegressor::predict(const Matrix& X) const
{
	return InferenceResult();
}

void NearestNeighborRegressor::save(std::ostream& out) const
{
}

void NearestNeighborRegressor::load(std::istream& in)
{
}
