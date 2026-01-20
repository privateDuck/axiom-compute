#pragma once

#include <definitions.hpp>


class IModel {
public:

	// No copy
	virtual void fit(const Matrix& X, const Vector& y) = 0;
	virtual InferenceResult predict(const Matrix& X) const = 0;

	virtual void save(std::ostream& out) const = 0;
	virtual void load(std::istream& in) = 0;

	virtual ~IModel() = default;
};