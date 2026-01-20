#pragma once

#include <Eigen/Eigen>

using EigenRowAlignedDoubleMat = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::AutoAlign>;
using EigenColAlignedDoubleMat = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::AutoAlign>;
using EigenRowAlignedFloatMat = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::AutoAlign>;
using EigenColAlignedFloatMat = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::AutoAlign>;

using EigenRowDoubleVec = Eigen::Matrix<double, 1, Eigen::Dynamic, Eigen::RowMajor | Eigen::AutoAlign>;
using EigenColDoubleVec = Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::AutoAlign>;
using EigenRowFloatVec = Eigen::Matrix<float, 1, Eigen::Dynamic, Eigen::RowMajor | Eigen::AutoAlign>;
using EigenColFloatVec = Eigen::Matrix<float, Eigen::Dynamic, 1, Eigen::AutoAlign>;