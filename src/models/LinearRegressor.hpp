#pragma once


#include "GenericModel.hpp"
#include "Common.hpp"
#include <mlpack.hpp>


class LinearRegressor : public IModel {
public:

	LinearRegressor(const double regularization, const bool intercept = true) : model_(), l2_reg(regularization), fit_intercept(intercept) {}

	// Inherited via IModel
	void fit(const Matrix& X, const Vector& y) override;
	InferenceResult predict(const Matrix& X) const override;
	void save(std::ostream& out) const override;
	void load(std::istream& in) override;

private:
	mlpack::LinearRegression<arma::mat> model_;		
	double l2_reg;
	bool fit_intercept;
};

class NearestNeighborRegressor : public IModel {
public:

	NearestNeighborRegressor(mlpack::neighbor::NeighborSearchMode search_mode, double epsilon, DistanceMetric metric) : model_(), search_mode_(search_mode), epsilon_(epsilon), distance_metric_(metric) {}
	
	// Inherited via IModel
	void fit(const Matrix& X, const Vector& y) override;
	InferenceResult predict(const Matrix& X) const override;
	void save(std::ostream& out) const override;
	void load(std::istream& in) override;

private:
	mlpack::neighbor::KNN model_;
	mlpack::neighbor::NeighborSearchMode search_mode_;
	double epsilon_;
	DistanceMetric distance_metric_;
};