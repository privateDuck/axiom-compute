#pragma once
#include <absl/container/flat_hash_map.h>

template<typename K, typename V>
using FHM = absl::flat_hash_map<K, V>;

template<typename T>
class OrdinalEncoder {
private:
	FHM<T, size_t> order_map;
	FHM<size_t, T> inverse_map;
public:
	OrdinalEncoder() = default;
	explicit OrdinalEncoder(const std::unordered_map<T, size_t>& order);

	void Fit(const std::vector<T>& data);
	Vector FitTransform(const std::vector<T>& data);
	Vector Transform(const std::vector<T>& data) const;

	std::vector<T> InverseTransform(const Vector& data) const;
	std::vector<T> GetCategories() const;
};


template<typename T>
class OneHotEncoder {
private:
	OrdinalEncoder ord_enc;

public:
	OneHotEncoder() = default;

	void Fit(const std::vector<T>& data);
	Vector FitTransformSparse(const std::vector<T>& data);
	Vector TransformSparse(const std::vector<T>& data) const;

	std::vector<Vector> FitTransformFull(const std::vector<T>& data);
	std::vector<Vector> TransformFull(const std::vector<T>& data) const;

	std::vector<T> InverseTransformSparse(const Vector& data) const;
	std::vector<T> InverseTransformFull(const std::vector<Vector>& data) const;

	std::vector<T> GetCategories() const;
};
