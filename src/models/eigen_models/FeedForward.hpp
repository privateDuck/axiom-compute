//
// Created by Tharuka on 25/01/2026.
//

//
// Modular Neural Network Implementation with Eigen
// Separated concerns: Model, Loss, Activation, Trainer, Regularization
//

#ifndef ATLAS_MODULAR_NN_HPP
#define ATLAS_MODULAR_NN_HPP
#pragma once

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <vector>
#include <variant>
#include <memory>
#include <functional>
#include <optional>
#include "EigenDefinitions.hpp"

namespace EigenModels {

// ============================================================================
// ACTIVATION FUNCTIONS
// ============================================================================

struct ActivationResult {
    MatrixR output;
    MatrixR z_cache;  // Pre-activation (for backward pass)
};

struct ReLU {
    [[nodiscard]] ActivationResult forward(const MatrixR& z) const {
        return {z.cwiseMax(0), z};
    }

    [[nodiscard]] MatrixR backward(const MatrixR& z_cache, const MatrixR& grad_output) const {
        return grad_output.cwiseProduct((z_cache.array() > 0).cast<Scalar>().matrix());
    }
};

struct Sigmoid {
    ActivationResult forward(const MatrixR& z) const {
        MatrixR output = z.unaryExpr([](Scalar x) {
            return 1.0f / (1.0f + std::exp(-x));
        });
        return {output, z};
    }

    MatrixR backward(const MatrixR& z_cache, const MatrixR& grad_output) const {
        // sigmoid'(z) = sigmoid(z) * (1 - sigmoid(z))
        MatrixR a = z_cache.unaryExpr([](const Scalar x) {
            return 1.0f / (1.0f + std::exp(-x));
        });
        return grad_output.cwiseProduct((a.array() * (1 - a.array())).matrix());
    }
};

struct Tanh {
    [[nodiscard]] ActivationResult forward(const MatrixR& z) const {
        MatrixR output = z.unaryExpr([](const Scalar x) { return std::tanh(x); });
        return {output, z};
    }

    [[nodiscard]] MatrixR backward(const MatrixR& z_cache, const MatrixR& grad_output) const {
        // tanh'(z) = 1 - tanh²(z)
        MatrixR a = z_cache.unaryExpr([](const Scalar x) { return std::tanh(x); });
        return grad_output.cwiseProduct((1 - a.array().square()).matrix());
    }
};

struct Softmax {
    [[nodiscard]] ActivationResult forward(const MatrixR& z) const {
        MatrixR output = z;
        for (int i = 0; i < output.rows(); ++i) {
            Scalar maxVal = output.row(i).maxCoeff();
            output.row(i) = (output.row(i).array() - maxVal).exp();
            output.row(i) /= output.row(i).sum();
        }
        return {output, z};
    }

    // Note: Softmax gradient is complex (Jacobian matrix per sample)
    // Usually combined with CrossEntropy for numerical stability
    // For standalone use, this is a simplified version
    [[nodiscard]] MatrixR backward(const MatrixR& z_cache, const MatrixR& grad_output) const {
        MatrixR a = forward(z_cache).output;
        MatrixR grad = MatrixR::Zero(grad_output.rows(), grad_output.cols());

        for (int i = 0; i < a.rows(); ++i) {
            // Jacobian: diag(a) - a * a^T
            EVector ai = a.row(i).transpose();
            MatrixC jacobian = ai.asDiagonal() - ai * ai.transpose();
            grad.row(i) = (jacobian * grad_output.row(i).transpose()).transpose();
        }
        return grad;
    }
};

struct Linear {
    ActivationResult forward(const MatrixR& z) const {
        return {z, z};
    }

    MatrixR backward(const MatrixR& z_cache, const MatrixR& grad_output) const {
        return grad_output;
    }
};

using ActivationFunc = std::variant<ReLU, Sigmoid, Tanh, Softmax, Linear>;

// ============================================================================
// REGULARIZATION
// ============================================================================

struct RegularizationResult {
    Scalar penalty;           // Regularization penalty to add to loss
    MatrixC weight_gradient;  // Gradient to add to weight gradients
};

struct NoRegularization {
    RegularizationResult compute(const MatrixC& weights) const {
        return {0.0f, MatrixC::Zero(weights.rows(), weights.cols())};
    }
};

struct L2Regularization {
    Scalar lambda;  // Regularization strength

    explicit L2Regularization(Scalar l = 0.01f) : lambda(l) {}

    RegularizationResult compute(const MatrixC& weights) const {
        // L2 penalty: λ/2 * ||W||²
        Scalar penalty = 0.5f * lambda * weights.array().square().sum();

        // L2 gradient: λ * W
        MatrixC gradient = lambda * weights;

        return {penalty, gradient};
    }
};

struct L1Regularization {
    Scalar lambda;  // Regularization strength

    explicit L1Regularization(Scalar l = 0.01f) : lambda(l) {}

    RegularizationResult compute(const MatrixC& weights) const {
        // L1 penalty: λ * ||W||₁
        Scalar penalty = lambda * weights.array().abs().sum();

        // L1 gradient: λ * sign(W)
        MatrixC gradient = lambda * weights.array().sign().matrix();

        return {penalty, gradient};
    }
};

struct ElasticNetRegularization {
    Scalar l1_lambda;  // L1 regularization strength
    Scalar l2_lambda;  // L2 regularization strength

    explicit ElasticNetRegularization(Scalar l1 = 0.01f, Scalar l2 = 0.01f)
        : l1_lambda(l1), l2_lambda(l2) {}

    RegularizationResult compute(const MatrixC& weights) const {
        // Elastic Net: α * L1 + (1-α) * L2
        // We use explicit l1_lambda and l2_lambda for more control

        Scalar l1_penalty = l1_lambda * weights.array().abs().sum();
        Scalar l2_penalty = 0.5f * l2_lambda * weights.array().square().sum();

        MatrixC l1_grad = l1_lambda * weights.array().sign().matrix();
        MatrixC l2_grad = l2_lambda * weights;

        return {l1_penalty + l2_penalty, l1_grad + l2_grad};
    }
};

using RegularizationFunc = std::variant<NoRegularization, L1Regularization, L2Regularization, ElasticNetRegularization>;

// ============================================================================
// LOSS FUNCTIONS
// ============================================================================

struct LossResult {
    Scalar value;
    MatrixR gradient;  // Gradient w.r.t predictions
};

struct MSELoss {
    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        MatrixR diff = predictions - targets;
        Scalar n = static_cast<Scalar>(predictions.rows());
        Scalar loss = diff.array().square().sum() / n;
        MatrixR grad = (2.0f / n) * diff;
        return {loss, grad};
    }
};

struct MAELoss {
    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        MatrixR diff = predictions - targets;
        Scalar n = static_cast<Scalar>(predictions.rows());
        Scalar loss = diff.array().abs().sum() / n;
        MatrixR grad = diff.array().sign().matrix() / n;
        return {loss, grad};
    }
};

struct CrossEntropyLoss {
    // Works with Softmax output (probabilities)
    // Targets should be one-hot encoded
    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        Scalar n = static_cast<Scalar>(predictions.rows());

        // Clip predictions for numerical stability
        MatrixR safe_pred = predictions.cwiseMax(1e-7f).cwiseMin(1.0f - 1e-7f);

        // Loss: -sum(y_true * log(y_pred)) / n
        Scalar loss = -(targets.array() * safe_pred.array().log()).sum() / n;

        // Gradient: (y_pred - y_true) / n
        // This is the combined gradient of Softmax + CrossEntropy
        MatrixR grad = (predictions - targets) / n;

        return {loss, grad};
    }
};

struct HuberLoss {
    Scalar delta = 1.0f;

    explicit HuberLoss(Scalar d = 1.0f) : delta(d) {}

    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        MatrixR diff = predictions - targets;
        Scalar n = static_cast<Scalar>(predictions.rows());

        Scalar loss = 0;
        MatrixR grad = MatrixR::Zero(diff.rows(), diff.cols());

        for (int i = 0; i < diff.size(); ++i) {
            Scalar abs_err = std::abs(diff(i));
            if (abs_err <= delta) {
                loss += 0.5f * abs_err * abs_err;
                grad(i) = diff(i);
            } else {
                loss += delta * (abs_err - 0.5f * delta);
                grad(i) = delta * (diff(i) > 0 ? 1.0f : -1.0f);
            }
        }

        return {loss / n, grad / n};
    }
};

struct MultiHingeLoss {
    Scalar margin = 1.0f;

    explicit MultiHingeLoss(Scalar m = 1.0f) : margin(m) {}

    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        const Scalar n = static_cast<Scalar>(predictions.rows());
        Scalar total_loss = 0;
        MatrixR grad = MatrixR::Zero(predictions.rows(), predictions.cols());

        for (int i = 0; i < n; ++i) {
            int correct_class;
            targets.row(i).maxCoeff(&correct_class);
            Scalar correct_score = predictions(i, correct_class);
            int violation_count = 0;

            for (int j = 0; j < predictions.cols(); ++j) {
                if (j == correct_class) continue;

                const Scalar loss_ij = margin - correct_score + predictions(i, j);
                if (loss_ij > 0) {
                    total_loss += loss_ij;
                    grad(i, j) = 1.0f;
                    violation_count++;
                }
            }

            grad(i, correct_class) = -static_cast<Scalar>(violation_count);
        }

        return {total_loss / n, grad / n};
    }
};

struct ZeroOneLoss {
    // Non-differentiable, for evaluation only
    LossResult forward(const MatrixR& predictions, const MatrixR& targets) const {
        const Scalar n = static_cast<Scalar>(predictions.rows());
        Scalar errors = 0;

        for (int i = 0; i < n; ++i) {
            int pred_idx, target_idx;
            predictions.row(i).maxCoeff(&pred_idx);
            targets.row(i).maxCoeff(&target_idx);
            if (pred_idx != target_idx) errors++;
        }

        // Zero gradient (not trainable)
        return {errors / n, MatrixR::Zero(predictions.rows(), predictions.cols())};
    }
};

using LossFunc = std::variant<MSELoss, MAELoss, CrossEntropyLoss, HuberLoss, MultiHingeLoss, ZeroOneLoss>;

// ============================================================================
// LAYER DEFINITION
// ============================================================================

struct Layer {
    MatrixC weights;
    EVector biases;

    // Gradients (computed during backward pass)
    MatrixC weight_grad;
    EVector bias_grad;

    // Caches for backpropagation
    MatrixR z_cache;       // Pre-activation
    MatrixR a_cache;       // Post-activation
    MatrixR input_cache;   // Input to this layer

    ActivationFunc activation;
    RegularizationFunc regularization;

    Layer(int in_size, int out_size, ActivationFunc act, RegularizationFunc reg = NoRegularization{})
        : activation(act), regularization(reg) {
        // Xavier/Glorot initialization
        const Scalar limit = std::sqrt(6.0f / static_cast<Scalar>(in_size + out_size));
        weights = MatrixR::Random(in_size, out_size) * limit;
        biases = EVector::Zero(out_size);
    }

    MatrixR forward(const MatrixR& input) {
        input_cache = input;
        z_cache = (input * weights).rowwise() + biases.transpose();

        ActivationResult act_result = std::visit(
            [&](const auto& act) { return act.forward(z_cache); },
            activation
        );

        a_cache = act_result.output;
        return a_cache;
    }

    MatrixR backward(const MatrixR& grad_output) {
        // Compute gradient w.r.t. pre-activation
        MatrixR grad_z = std::visit(
            [&](const auto& act) { return act.backward(z_cache, grad_output); },
            activation
        );

        // Compute gradients for weights and biases
        weight_grad = input_cache.transpose() * grad_z;
        bias_grad = grad_z.colwise().sum();

        // Add regularization gradient to weight gradients
        RegularizationResult reg_result = std::visit(
            [&](const auto& reg) { return reg.compute(weights); },
            regularization
        );
        weight_grad += reg_result.weight_gradient;

        // Compute gradient w.r.t. input (for previous layer)
        return grad_z * weights.transpose();
    }

    // Compute regularization penalty for this layer
    Scalar getRegularizationPenalty() const {
        return std::visit(
            [&](const auto& reg) { return reg.compute(weights).penalty; },
            regularization
        );
    }
};

// ============================================================================
// MODEL (Just holds architecture and parameters)
// ============================================================================

class FeedForwardNN {
public:
    FeedForwardNN() = default;

    void addLayer(int in_size, int out_size, ActivationFunc activation,
                  RegularizationFunc regularization = NoRegularization{}) {
        layers.emplace_back(in_size, out_size, std::move(activation), std::move(regularization));
    }

    MatrixR forward(const MatrixR& input) {
        MatrixR curr = input;
        for (auto& layer : layers) {
            curr = layer.forward(curr);
        }
        return curr;
    }

    void backward(const MatrixR& grad_output) {
        MatrixR grad = grad_output;
        for (int i = static_cast<int>(layers.size()) - 1; i >= 0; --i) {
            grad = layers[i].backward(grad);
        }
    }

    // Compute total regularization penalty across all layers
    Scalar getRegularizationPenalty() const {
        Scalar total = 0.0f;
        for (const auto& layer : layers) {
            total += layer.getRegularizationPenalty();
        }
        return total;
    }

    std::vector<Layer>& getLayers() { return layers; }
    const std::vector<Layer>& getLayers() const { return layers; }

    // Zero out all gradients
    void zeroGrad() {
        for (auto& layer : layers) {
            layer.weight_grad.setZero();
            layer.bias_grad.setZero();
        }
    }

private:
    std::vector<Layer> layers;
};

// ============================================================================
// TRAINER (Orchestrates training loop)
// ============================================================================

class Trainer {
public:
    Trainer(FeedForwardNN& model, LossFunc loss_fn)
        : model_(model), loss_fn_(std::move(loss_fn)) {}

    // Single training step
    // Returns: {data_loss, regularization_penalty, total_loss}
    std::tuple<Scalar, Scalar, Scalar> trainStep(const MatrixR& input, const MatrixR& targets) {
        // Forward pass
        MatrixR predictions = model_.forward(input);

        // Compute loss and its gradient
        LossResult loss_result = std::visit(
            [&](const auto& loss) { return loss.forward(predictions, targets); },
            loss_fn_
        );

        // Get regularization penalty
        Scalar reg_penalty = model_.getRegularizationPenalty();

        // Total loss = data loss + regularization penalty
        Scalar total_loss = loss_result.value + reg_penalty;

        // Backward pass (regularization gradients are added automatically in Layer::backward)
        model_.backward(loss_result.gradient);

        return {loss_result.value, reg_penalty, total_loss};
    }

    // Evaluation (no gradient computation needed in model)
    // Returns: {data_loss, regularization_penalty, total_loss}
    std::tuple<Scalar, Scalar, Scalar> evaluate(const MatrixR& input, const MatrixR& targets) {
        MatrixR predictions = model_.forward(input);

        LossResult loss_result = std::visit(
            [&](const auto& loss) { return loss.forward(predictions, targets); },
            loss_fn_
        );

        Scalar reg_penalty = model_.getRegularizationPenalty();
        Scalar total_loss = loss_result.value + reg_penalty;

        return {loss_result.value, reg_penalty, total_loss};
    }

    // Get predictions without computing loss
    MatrixR predict(const MatrixR& input) {
        return model_.forward(input);
    }

private:
    FeedForwardNN& model_;
    LossFunc loss_fn_;
};

} // namespace EigenModels

#endif // ATLAS_MODULAR_NN_HPP