//
// Created by Tharuka on 27/01/2026.
//

#ifndef ATLAS_LINEAR_HPP
#define ATLAS_LINEAR_HPP
#pragma once

#include "EigenDefinitions.hpp"
#include "LBFGSpp/LBFGS.h"
#include "FeedForward.hpp"

namespace EigenModels {

// LBFGSpp requires: operator() for loss and gradient computation
class LinearModelProblem {
public:
    LinearModelProblem(const MatrixR& X, const MatrixR& y, LossFunc loss, RegularizationFunc reg)
        : X_(X), y_(y), loss_fn_(std::move(loss)), reg_fn_(std::move(reg)) {
        n_samples_ = X.rows();
        n_features_ = X.cols();
        n_outputs_ = y.cols();
    }

    // LBFGSpp interface: compute loss
    Scalar operator()(const Eigen::VectorXf& params, Eigen::VectorXf& grad) {
        // Unpack parameters into weights and biases
        MatrixR W = Eigen::Map<const MatrixR>(
            params.data(), n_features_, n_outputs_
        );
        EVector b = Eigen::Map<const EVector>(
            params.data() + n_features_ * n_outputs_, n_outputs_
        );

        // Forward pass: predictions = X * W + b
        MatrixR predictions = (X_ * W).rowwise() + b.transpose();

        // Compute data loss and gradient
        LossResult loss_result = std::visit(
            [&](const auto& loss) { return loss.forward(predictions, y_); },
            loss_fn_
        );

        Scalar data_loss = loss_result.value;
        MatrixR grad_pred = loss_result.gradient;

        // Compute regularization
        RegularizationResult reg_result = std::visit(
            [&](const auto& reg) { return reg.compute(W); },
            reg_fn_
        );

        Scalar total_loss = data_loss + reg_result.penalty;

        // Compute gradients
        // dL/dW = X^T * grad_pred + reg_gradient
        MatrixR grad_W = X_.transpose() * grad_pred + reg_result.weight_gradient;

        // dL/db = sum(grad_pred) across samples
        EVector grad_b = grad_pred.colwise().sum();

        // Pack gradients into single vector
        Eigen::Map<MatrixR>(grad.data(), n_features_, n_outputs_) = grad_W;
        Eigen::Map<EVector>(grad.data() + n_features_ * n_outputs_, n_outputs_) = grad_b;

        return total_loss;
    }

    [[nodiscard]] int64_t num_params() const {
        return n_features_ * n_outputs_ + n_outputs_;
    }

private:
    const MatrixR& X_;
    const MatrixR& y_;
    LossFunc loss_fn_;
    RegularizationFunc reg_fn_;
    int64_t n_samples_;
    int64_t n_features_;
    int64_t n_outputs_;
};

// ============================================================================
// LINEAR MODEL BASE (using LBFGS)
// ============================================================================

class LinearModelLBFGS {
public:
    LinearModelLBFGS(LossFunc loss, RegularizationFunc reg)
        : loss_fn_(std::move(loss)), reg_fn_(std::move(reg)), fitted_(false) {}

    void fit(const MatrixR& X, const MatrixR& y, int max_iterations = 100) {
        n_features_ = X.cols();
        n_outputs_ = y.cols();

        // Initialize parameters (Xavier initialization)
        const Scalar limit = std::sqrt(6.0f / static_cast<Scalar>(n_features_ + n_outputs_));
        weights_ = MatrixR::Random(n_features_, n_outputs_) * limit;
        biases_ = EVector::Zero(n_outputs_);

        // Pack parameters into single vector for LBFGS
        Eigen::VectorXf params(n_features_ * n_outputs_ + n_outputs_);
        Eigen::Map<MatrixR>(params.data(), n_features_, n_outputs_) = weights_;
        Eigen::Map<EVector>(params.data() + n_features_ * n_outputs_, n_outputs_) = biases_;

        // Create optimization problem
        LinearModelProblem problem(X, y, loss_fn_, reg_fn_);

        // Setup LBFGS
        LBFGSpp::LBFGSParam<Scalar> param;
        param.epsilon = 1e-6;
        param.max_iterations = max_iterations;

        LBFGSpp::LBFGSSolver<Scalar> solver(param);
        Scalar final_loss;

        // Optimize
        int niter = solver.minimize(problem, params, final_loss);

        // Unpack optimized parameters
        weights_ = Eigen::Map<MatrixR>(params.data(), n_features_, n_outputs_);
        biases_ = Eigen::Map<EVector>(params.data() + n_features_ * n_outputs_, n_outputs_);

        fitted_ = true;
        last_loss_ = final_loss;
        iterations_ = niter;
    }

    [[nodiscard]] MatrixR predict(const MatrixR& X) const {
        if (!fitted_) {
            throw std::runtime_error("Model not fitted yet!");
        }
        return (X * weights_).rowwise() + biases_.transpose();
    }

    [[nodiscard]] Scalar evaluate(const MatrixR& X, const MatrixR& y) const {
        MatrixR predictions = predict(X);
        LossResult result = std::visit(
            [&](const auto& loss) { return loss.forward(predictions, y); },
            loss_fn_
        );

        RegularizationResult reg_result = std::visit(
            [&](const auto& reg) { return reg.compute(weights_); },
            reg_fn_
        );

        return result.value + reg_result.penalty;
    }

    [[nodiscard]] const MatrixR& getWeights() const { return weights_; }
    [[nodiscard]] const EVector& getBiases() const { return biases_; }
    [[nodiscard]] Scalar getLastLoss() const { return last_loss_; }
    [[nodiscard]] int64_t getIterations() const { return iterations_; }

protected:
    LossFunc loss_fn_;
    RegularizationFunc reg_fn_;
    MatrixR weights_;
    EVector biases_;
    int64_t n_features_{};
    int64_t n_outputs_{};
    int64_t iterations_{};
    Scalar last_loss_{};
    bool fitted_;
};

// ============================================================================
// SPECIFIC MODEL IMPLEMENTATIONS
// ============================================================================

// Linear Regression (MSE Loss)
class LinearRegression : public LinearModelLBFGS {
public:
    explicit LinearRegression(RegularizationFunc reg = NoRegularization{})
        : LinearModelLBFGS(MSELoss{}, std::move(reg)) {}
};

// Ridge Regression (MSE Loss + L2 Regularization)
class RidgeRegression : public LinearModelLBFGS {
public:
    explicit RidgeRegression(Scalar alpha = 1.0f)
        : LinearModelLBFGS(MSELoss{}, L2Regularization{alpha}) {}
};

// Lasso Regression (MSE Loss + L1 Regularization)
class LassoRegression : public LinearModelLBFGS {
public:
    explicit LassoRegression(Scalar alpha = 1.0f)
        : LinearModelLBFGS(MSELoss{}, L1Regularization{alpha}) {}
};

// ElasticNet Regression (MSE Loss + L1 + L2)
class ElasticNetRegression : public LinearModelLBFGS {
public:
    explicit ElasticNetRegression(Scalar l1_ratio = 0.5f, Scalar alpha = 1.0f)
        : LinearModelLBFGS(MSELoss{}, ElasticNetRegularization{l1_ratio * alpha, (1 - l1_ratio) * alpha}) {}
};

// Logistic Regression (Binary or Multiclass with Softmax + CrossEntropy)
class LogisticRegression : public LinearModelLBFGS {
public:
    explicit LogisticRegression(RegularizationFunc reg = NoRegularization{})
        : LinearModelLBFGS(CrossEntropyLoss{}, std::move(reg)) {}

    // Override predict to apply softmax
    [[nodiscard]] MatrixR predict(const MatrixR& X) const {
        if (!fitted_) {
            throw std::runtime_error("Model not fitted yet!");
        }

        const MatrixR logits = (X * weights_).rowwise() + biases_.transpose();

        // Apply softmax for probabilities
        constexpr Softmax softmax;
        return softmax.forward(logits).output;
    }

    // Predict class labels (argmax)
    [[nodiscard]] Eigen::VectorXi predictClasses(const MatrixR& X) const {
        MatrixR probs = predict(X);
        Eigen::VectorXi labels(probs.rows());

        for (int i = 0; i < probs.rows(); ++i) {
            probs.row(i).maxCoeff(&labels(i));
        }

        return labels;
    }

    // Get raw logits (no softmax)
    [[nodiscard]] MatrixR predictLogits(const MatrixR& X) const {
        if (!fitted_) {
            throw std::runtime_error("Model not fitted yet!");
        }
        return (X * weights_).rowwise() + biases_.transpose();
    }
};

// Linear SVM (Hinge Loss)
class LinearSVM : public LinearModelLBFGS {
public:
    explicit LinearSVM(const Scalar C = 1.0f)
        : LinearModelLBFGS(MultiHingeLoss{1.0f}, L2Regularization(2.0f/C)), C_(C) {}

    // Override fit to scale regularization by C
    void fit(const MatrixR& X, const MatrixR& y, int max_iterations = 100) {
        // SVM convention: minimize (1/C)||w||² + Σ hinge_loss
        // Equivalent to: minimize hinge_loss + (1/2C)λ||w||²
        // So we need to adjust regularization strength based on C
        // λ = 2/C
        LinearModelLBFGS::fit(X, y, max_iterations);
    }

    // Predict class labels (argmax of scores)
    [[nodiscard]] Eigen::VectorXi predictClasses(const MatrixR& X) const {
        MatrixR scores = predict(X);
        Eigen::VectorXi labels(scores.rows());

        for (int i = 0; i < scores.rows(); ++i) {
            scores.row(i).maxCoeff(&labels(i));
        }

        return labels;
    }

    // Get decision function values
    [[nodiscard]] MatrixR decisionFunction(const MatrixR& X) const {
        return predict(X);
    }

private:
    Scalar C_;  // Regularization parameter
};

// ============================================================================
// ALTERNATIVE: SINGLE LAYER NN APPROACH (for comparison)
// ============================================================================

// This shows how you could also use the existing NN infrastructure
// But LBFGS-specific classes above are cleaner and more efficient

template<typename OptimizerType>
class LinearModelNN {
public:
    LinearModelNN(int input_dim, int output_dim,
                  ActivationFunc activation,
                  LossFunc loss,
                  RegularizationFunc reg = NoRegularization{})
        : optimizer_(std::make_unique<OptimizerType>()) {

        model_.addLayer(input_dim, output_dim, std::move(activation), std::move(reg));
        trainer_ = std::make_unique<Trainer>(model_, std::move(loss));
    }

    void fit(const MatrixR& X, const MatrixR& y, int epochs = 100) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            optimizer_->zeroGrad(model_);
            auto [data_loss, reg_penalty, total_loss] = trainer_->trainStep(X, y);
            optimizer_->step(model_);
        }
    }

    [[nodiscard]] MatrixR predict(const MatrixR& X) const {
        return trainer_->predict(X);
    }

private:
    FeedForwardNN model_;
    std::unique_ptr<Trainer> trainer_;
    std::unique_ptr<OptimizerType> optimizer_;
};

} // namespace EigenModels

#endif //ATLAS_LINEAR_HPP