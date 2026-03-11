//
// Created by Tharuka on 28/01/2026.
//

#ifndef ATLAS_SAMPLER_HPP
#define ATLAS_SAMPLER_HPP
#pragma once

#include <Eigen/Dense>
#include <random>
#include <algorithm>
#include <vector>
#include <map>
#include <concepts>
#include <numeric>

// Concept for Eigen matrix types
template<typename T>
concept EigenMatrix = requires(T m) {
    { m.rows() } -> std::convertible_to<Eigen::Index>;
    { m.cols() } -> std::convertible_to<Eigen::Index>;
};

// Concept for float or double
template<typename T>
concept FloatingPoint = std::is_same_v<T, float> || std::is_same_v<T, double>;

// 1. Randomize rows of X and Y while maintaining correspondence
template<FloatingPoint Scalar>
void randomize_rows(
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    std::mt19937& rng)
{
    assert(X.rows() == Y.rows());

    const Eigen::Index n_rows = X.rows();
    std::vector<Eigen::Index> indices(n_rows);
    std::iota(indices.begin(), indices.end(), 0);

    std::ranges::shuffle(indices, rng);

    // Create temporary copies
    auto X_copy = X.eval();
    auto Y_copy = Y.eval();

    // Reorder rows
    for (Eigen::Index i = 0; i < n_rows; ++i) {
        X.row(i) = X_copy.row(indices[i]);
        Y.row(i) = Y_copy.row(indices[i]);
    }
}

// Overload with seed
template<FloatingPoint Scalar>
void randomize_rows(
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    unsigned int seed = std::random_device{}())
{
    std::mt19937 rng(seed);
    randomize_rows(X, Y, rng);
}

// 2a. Split X and Y into two matrices (non-stratified, returns new matrices)
template<FloatingPoint Scalar>
struct SplitResult {
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> X_first;
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Y_first;
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> X_second;
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Y_second;
};

template<FloatingPoint Scalar>
SplitResult<Scalar> split_rows(
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    double ratio)
{
    assert(X.rows() == Y.rows());
    assert(ratio > 0.0 && ratio < 1.0);

    const Eigen::Index n_rows = X.rows();
    const auto split_point = static_cast<Eigen::Index>(n_rows * ratio);

    SplitResult<Scalar> result;
    result.X_first = X.topRows(split_point);
    result.Y_first = Y.topRows(split_point);
    result.X_second = X.bottomRows(n_rows - split_point);
    result.Y_second = Y.bottomRows(n_rows - split_point);

    return result;
}

// 2b. Split X and Y in-place using Eigen::Map
template<FloatingPoint Scalar>
struct SplitResultMap {
    Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> X_first;
    Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_first;
    Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> X_second;
    Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> Y_second;
};

template<FloatingPoint Scalar>
SplitResultMap<Scalar> split_rows_inplace(
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    double ratio)
{
    assert(X.rows() == Y.rows());
    assert(ratio > 0.0 && ratio < 1.0);

    const Eigen::Index n_rows = X.rows();
    const auto split_point = static_cast<Eigen::Index>(n_rows * ratio);
    const Eigen::Index x_cols = X.cols();
    const Eigen::Index y_cols = Y.cols();

    return SplitResultMap<Scalar>{
        Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(
            X.data(), split_point, x_cols),
        Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(
            Y.data(), split_point, y_cols),
        Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(
            X.data() + split_point * x_cols, n_rows - split_point, x_cols),
        Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(
            Y.data() + split_point * y_cols, n_rows - split_point, y_cols)
    };
}

// 2c. Stratified split based on Y (for classification tasks)
template<FloatingPoint Scalar>
SplitResult<Scalar> split_rows_stratified(
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    double ratio,
    std::mt19937& rng)
{
    assert(X.rows() == Y.rows());
    assert(ratio > 0.0 && ratio < 1.0);

    const Eigen::Index n_rows = X.rows();

    // Group indices by class label
    std::map<Scalar, std::vector<Eigen::Index>> class_indices;
    for (Eigen::Index i = 0; i < n_rows; ++i) {
        class_indices[Y(i, 0)].push_back(i);
    }

    std::vector<Eigen::Index> first_indices, second_indices;

    // Split each class proportionally
    for (auto& [label, indices] : class_indices) {
        std::shuffle(indices.begin(), indices.end(), rng);
        const auto split = static_cast<size_t>(indices.size() * ratio);

        first_indices.insert(first_indices.end(), indices.begin(), indices.begin() + split);
        second_indices.insert(second_indices.end(), indices.begin() + split, indices.end());
    }

    // Create result matrices
    SplitResult<Scalar> result;
    result.X_first.resize(first_indices.size(), X.cols());
    result.Y_first.resize(first_indices.size(), Y.cols());
    result.X_second.resize(second_indices.size(), X.cols());
    result.Y_second.resize(second_indices.size(), Y.cols());

    for (size_t i = 0; i < first_indices.size(); ++i) {
        result.X_first.row(i) = X.row(first_indices[i]);
        result.Y_first.row(i) = Y.row(first_indices[i]);
    }

    for (size_t i = 0; i < second_indices.size(); ++i) {
        result.X_second.row(i) = X.row(second_indices[i]);
        result.Y_second.row(i) = Y.row(second_indices[i]);
    }

    return result;
}

// Overload with seed
template<FloatingPoint Scalar>
SplitResult<Scalar> split_rows_stratified(
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    double ratio,
    unsigned int seed = std::random_device{}())
{
    std::mt19937 rng(seed);
    return split_rows_stratified(X, Y, ratio, rng);
}

// 3. Sort X and Y based on Y (single column)
template<FloatingPoint Scalar>
void sort_by_y(
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& X,
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>& Y,
    const bool ascending = true)
{
    assert(X.rows() == Y.rows());
    assert(Y.cols() == 1);

    const Eigen::Index n_rows = X.rows();
    std::vector<Eigen::Index> indices(n_rows);
    std::iota(indices.begin(), indices.end(), 0);

    // Sort indices based on Y values
    if (ascending) {
        std::sort(indices.begin(), indices.end(),
            [&Y](Eigen::Index i1, Eigen::Index i2) {
                return Y(i1, 0) < Y(i2, 0);
            });
    } else {
        std::sort(indices.begin(), indices.end(),
            [&Y](Eigen::Index i1, Eigen::Index i2) {
                return Y(i1, 0) > Y(i2, 0);
            });
    }

    // Create temporary copies
    auto X_copy = X.eval();
    auto Y_copy = Y.eval();

    // Reorder rows
    for (Eigen::Index i = 0; i < n_rows; ++i) {
        X.row(i) = X_copy.row(indices[i]);
        Y.row(i) = Y_copy.row(indices[i]);
    }
}

#endif //ATLAS_SAMPLER_HPP