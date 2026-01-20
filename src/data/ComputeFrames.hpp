#pragma once


#include <EigenDefinitions.hpp>
#include <../transformers/Encoder.hpp>
#include <HashMap.hpp>
#include <../data/FastHash.hpp>

struct NumericalColumn {
	Eigen::Matrix<float, 1, -1> data;
};

struct CategoricalColumn {
	Eigen::Matrix<float, 1, -1> encoded_data;
	std::vector<std::string> actual_data;
	OrdinalEncoder<std::string> encoder;
};

enum class ComputeColumnType {
	Numeric,
	Categoric
};

struct ColumnMeta {
	std::string name;
	ComputeColumnType type;
};

// An object that holds the base reference data frame.
// Actually stores the categorical columns
class ReferenceDataFrame {
private:
	HashMapStrT<CategoricalColumn> cats;
};

class ComputeFrame {
public:
	std::vector<ColumnMeta> columns;
	EigenRowAlignedFloatMat X;
	const ReferenceDataFrame* pRefDF;

	ComputeFrame(uint64_t num_features, uint64_t cat_features, uint64_t rows)
	{
		EmbeddedOneWayFlatMap a;
		uint64_t total_X_bytes = (num_features * rows + cat_features * rows) * sizeof(float);
		uint64_t hash_maps = cat_features * sizeof(EmbeddedFlatMap<2048>);
		uint64_t total_features = num_features + cat_features;
		data_ptr = std::move(std::make_unique<uint8_t>(total_X_bytes + hash_maps));
		float* dptr = reinterpret_cast<float*>(data_ptr.get());
		X = Eigen::Map<EigenRowAlignedFloatMat>(dptr, rows, total_features);
	}
private:
	std::unique_ptr<uint8_t> data_ptr;
};


class ComputeFrameBuilder {

};