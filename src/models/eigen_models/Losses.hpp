//
// Created by Tharuka on 26/01/2026.
//

#ifndef ATLAS_LOSSES_HPP
#define ATLAS_LOSSES_HPP
#pragma once

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>
#include <cmath>
#include "EigenDefinitions.hpp"

namespace EigenModels {
    using MatrixR = EigenRowAlignedFloatMat;
    using MatrixC = EigenColAlignedFloatMat;
    using EVector = EigenColFloatVec;

    struct MSE {
        // 1. Cost (Scalar)
        static Scalar cost(const MatrixR& pred, const MatrixR& target) {
            return (pred - target).array().square().sum() / static_cast<float>(pred.rows());
        }

        // 2. Gradient (Matrix) - Returns dL/dA
        static MatrixR grad(const MatrixR& pred, const MatrixR& target) {
            return (2.0f / static_cast<float>(pred.rows())) * (pred - target);
        }
    };
}
#endif //ATLAS_LOSSES_HPP