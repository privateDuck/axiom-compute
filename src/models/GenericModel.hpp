#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "definitions.hpp"

class IModel {
public:
	virtual void fit(const Matrix& X, const Vector& y) = 0;
	virtual InferenceResult predict(const Matrix& X) const = 0;

	virtual void save(std::ostream& out) const = 0;
	virtual void load(std::istream& in) = 0;

	virtual ~IModel() = default;
};


class IModelFactory {
public:
	virtual std::unique_ptr<IModel> createModel(const ParameterSet& parameters) const = 0;
	virtual ~IModelFactory() = default;
};