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
	std::vector<EigenColDoubleVec> columns_data;
	EigenColAlignedDoubleMat numX;
	EigenColAlignedDoubleMat catX;
	const ReferenceDataFrame* pRefDF;

	void BuildFromReference(const ReferenceDataFrame* refDF)
	{
		pRefDF = refDF;
		size_t all_elements = cols * rows;
		data_ptr = std::move(std::make_unique<double>(all_elements));
		auto* ptrNumX = data_ptr.get();
		auto* ptrCatX = data_ptr.get() + num_features * rows;
		numX = Eigen::Map<EigenColAlignedDoubleMat>(ptrNumX, rows, num_features);
		catX = Eigen::Map<EigenColAlignedDoubleMat>(ptrCatX, rows, cat_features);
	}
private:
	std::unique_ptr<double> data_ptr;
};


class ComputeFrameBuilder {

};