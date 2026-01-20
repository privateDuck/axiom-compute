#include "EigenDataset.hpp"

EigenDataset::EigenDataset(const EigenRowAlignedDoubleMat& X, const EigenRowDoubleVec& y)
{
	auto options = torch::TensorOptions().dtype(torch::kFloat32);
	_inputs = torch::empty({ (long)X.rows(), (long)X.cols() }, options);
	_targets = torch::empty({ (long)y.rows() }, options);

	auto inputs_accessor = _inputs.accessor<float, 2>();
	auto targets_accessor = _targets.accessor<float, 1>();

	for (long i = 0; i < X.rows(); ++i) {
		for (long j = 0; j < X.cols(); ++j) {
			inputs_accessor[i][j] = static_cast<float>(X(i, j));
		}
	}

	for (long i = 0; i < y.rows(); ++i) {
		targets_accessor[i] = static_cast<float>(y(i));
	}
}

EigenDataset::EigenDataset(const EigenColAlignedDoubleMat& X, const EigenColDoubleVec& y)
{
	auto options = torch::TensorOptions().dtype(torch::kFloat32);
	_inputs = torch::empty({ (long)X.rows(), (long)X.cols() }, options);
	_targets = torch::empty({ (long)y.rows() }, options);

	auto inputs_accessor = _inputs.accessor<float, 2>();
	auto targets_accessor = _targets.accessor<float, 1>();

	for (long i = 0; i < X.rows(); ++i) {
		for (long j = 0; j < X.cols(); ++j) {
			inputs_accessor[i][j] = static_cast<float>(X(i, j));
		}
	}

	for (long i = 0; i < y.rows(); ++i) {
		targets_accessor[i] = static_cast<float>(y(i));
	}
}

EigenDataset::EigenDataset(const EigenRowAlignedFloatMat& X, const EigenRowFloatVec& y)
{
	_inputs = torch::from_blob(
		const_cast<float*>(X.data()),
		{ X.rows(), X.cols() },
		torch::kFloat32
	).clone();

	_targets = torch::from_blob(
		const_cast<float*>(y.data()),
		{ y.rows() },
		torch::kFloat32
	).clone();
}

EigenDataset::EigenDataset(const EigenColAlignedFloatMat& X, const EigenColFloatVec& y)
{
	auto options = torch::TensorOptions().dtype(torch::kFloat32);
	_inputs = torch::empty({ (long)X.rows(), (long)X.cols() }, options);
	_targets = torch::empty({ (long)y.rows() }, options);

	auto inputs_accessor = _inputs.accessor<float, 2>();
	auto targets_accessor = _targets.accessor<float, 1>();

	for (long i = 0; i < X.rows(); ++i) {
		for (long j = 0; j < X.cols(); ++j) {
			inputs_accessor[i][j] = X(i, j);
		}
	}

	for (long i = 0; i < y.rows(); ++i) {
		targets_accessor[i] = y(i);
	}
}

torch::data::Example<> EigenDataset::get(size_t index)
{
	return { _inputs[index], _targets[index] };
}

torch::optional<size_t> EigenDataset::size() const
{
	return _inputs.size(0);
}
