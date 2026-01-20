#pragma once

#include <Eigen/Eigen>
#include <torch/torch.h>
#include <torch/data.h>
#include <EigenDefinitions.hpp>

// Wrapper for Eigen matrices to be used as Libtorch datasets
// Fixed 32bit precision tensors
struct EigenDataset : public torch::data::datasets::Dataset<EigenDataset> {
private:
	torch::Tensor _inputs;
	torch::Tensor _targets;

public:
	EigenDataset(const EigenRowAlignedDoubleMat& X, const EigenRowDoubleVec& y);
	EigenDataset(const EigenColAlignedDoubleMat& X, const EigenColDoubleVec& y);
	EigenDataset(const EigenRowAlignedFloatMat& X, const EigenRowFloatVec& y);
	EigenDataset(const EigenColAlignedFloatMat& X, const EigenColFloatVec& y);

	torch::data::Example<> get(size_t index) override;

	torch::optional<size_t> size() const override;
};