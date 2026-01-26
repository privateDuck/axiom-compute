//
// Created by Tharuka on 25/01/2026.
//

#ifndef ATLAS_FEEDFORWARD_HPP
#define ATLAS_FEEDFORWARD_HPP
#pragma once

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>
#include <cmath>
#include "EigenDefinitions.hpp"
#include "Losses.hpp"

namespace EigenModels {
    enum class Activation { None, ReLU, Sigmoid, Tanh, Softmax };
    enum class LossType { MSE, MAE, CrossEntropy, Huber, MultiHinge, ZeroOne };

    struct Math {
        static MatrixR applyActivation(const MatrixR& z, const Activation act) {
            switch (act) {
                case Activation::ReLU: return z.cwiseMax(0);
                case Activation::Sigmoid: return z.unaryExpr([](const Scalar x){ return 1.0f / (1.0f + std::exp(-x)); });
                case Activation::Tanh: return z.unaryExpr([](const Scalar x){ return std::tanh(x); });
                case Activation::Softmax: {
                    // Stable Softmax applied row-wise (batch)
                    MatrixR res = z;
                    for (int i = 0; i < res.rows(); ++i) {
                        Scalar maxVal = res.row(i).maxCoeff();
                        res.row(i) = (res.row(i).array() - maxVal).exp();
                        res.row(i) /= res.row(i).sum();
                    }
                    return res;
                }
                default: return z;
            }
        }

        // Computes d(Activation)/d(Z) * d(Loss)/d(A)
        // For element-wise activations, we compute d(Act)/d(Z) and multiply by error signal
        static MatrixR applyDerivative(const MatrixR& z, const MatrixR& a, const MatrixR& upstreamGrad, Activation act) {
            switch (act) {
                case Activation::ReLU:
                    return upstreamGrad.cwiseProduct((z.array() > 0).cast<Scalar>().matrix());
                case Activation::Sigmoid:
                    // sigmoid'(z) = a * (1 - a)
                    // also possible : (upstreamGrad.array() * a.array() * (1 - a.array())).matrix();
                    return upstreamGrad.cwiseProduct((a.array() * (1 - a.array())).matrix());
                case Activation::Tanh:
                    // tanh'(z) = 1 - a^2
                    // (upstreamGrad.array() * (1 - a.array().square())).matrix();
                    return upstreamGrad.cwiseProduct((1 - a.array().square()).matrix());
                case Activation::Softmax:
                    // Softmax derivative is complex (Jacobian).
                    // Usually combined with CrossEntropy for simplification (Pred - Target).
                    // If isolated, we handle it in the backward pass logic specifically.
                    // return upstreamGrad;
                default: return upstreamGrad;
            }
        }
    };

    struct Layer {
        MatrixC weights;
        EVector biases;
        MatrixC weightsGrad;
        EVector biasesGrad;

        // Cache for backprop
        MatrixR z_cache; // Pre-activation
        MatrixR a_cache; // Post-activation
        Activation activation;

        Layer(const int inSize, const int outSize, const Activation act) : activation(act) {
            // TODO: Proper Xavier/Glorot Initialization
            const Scalar limit = std::sqrt(6.0f / static_cast<float>(inSize + outSize));
            weights = MatrixR::Random(inSize, outSize) * limit;
            biases = EVector::Zero(outSize);
        }
    };


    class FeedForwardNN {
    public:
        FeedForwardNN(const std::vector<uint32_t>& topology, const Activation activation, const LossType loss) {

        }

        void addLayer(int inSize, int outSize, Activation act) {
            layers.emplace_back(inSize, outSize, act);
        }

        MatrixR forward(const MatrixR& input) {
            MatrixR curr = input;

            for (auto& layer : layers) {
                layer.z_cache = (curr * layer.weights).rowwise() + layer.biases.transpose();
                layer.a_cache = Math::applyActivation(layer.z_cache, layer.activation);
                curr = layer.a_cache;
            }
            return curr;
        }

        [[nodiscard]] Scalar computeLoss(const MatrixR& predictions, const MatrixR& targets, const LossType lossType) const {
        MatrixR diff = predictions - targets;
        const auto n = static_cast<float>(predictions.rows()); // Batch size

        switch (lossType) {
            case LossType::MSE:
                return diff.array().square().sum() / n;
            case LossType::MAE:
                return diff.array().abs().sum() / n;
            case LossType::Huber: {
                Scalar loss = 0;
                for(int i=0; i<diff.size(); ++i) {
                    const Scalar absErr = std::abs(diff(i));
                    loss += (absErr <= huberDelta) ? 0.5f * absErr * absErr : huberDelta * (absErr - 0.5f * huberDelta);
                }
                return loss / n;
            }
            case LossType::CrossEntropy: {
                // assumes Softmax was applied. CE = -sum(y_true * log(y_pred))
                // Add epsilon for stability
                MatrixR safePred = predictions.cwiseMax(1e-7).cwiseMin(1.0f - 1e-7);
                return -(targets.array() * safePred.array().log()).sum() / n;
            }
            case LossType::ZeroOne: {
                 // Not differentiable, purely metric.
                 Scalar errors = 0;
                 for(int i=0; i<n; ++i) {
                     int predIdx, targetIdx;
                     predictions.row(i).maxCoeff(&predIdx);
                     targets.row(i).maxCoeff(&targetIdx);
                     if(predIdx != targetIdx) errors++;
                 }
                 return errors / n;
            }
            case LossType::MultiHinge: {
                // L = sum(max(0, 1 + y_wrong - y_correct))
                Scalar totalLoss = 0;
                for (int i = 0; i<n; ++i) {
                    int correctClass;
                    targets.row(i).maxCoeff(&correctClass); // Assuming one-hot targets
                    const Scalar correctScore = predictions(i, correctClass);

                    for (int j = 0; j<predictions.cols(); ++j) {
                        if (j == correctClass) continue;
                        totalLoss += std::max(0.0f, hingeMargin - correctScore + predictions(i, j));
                    }
                }
                return totalLoss / n;
            }
            default: return 0.0f;
        }
    }

    void backward(const MatrixR& input, const MatrixR& predictions, const MatrixR& targets, const LossType lossType) {
        const auto n = static_cast<float>(input.rows());
        MatrixR grad; // Gradient of Loss w.r.t the output of the current layer (dL/dA) or (dL/dZ)

        // 1. Compute Gradient at Output Layer
        // We calculate dL/dZ (gradient w.r.t pre-activation) directly for efficiency/stability where possible

        const bool outputIsSoftmax = (!layers.empty() && layers.back().activation == Activation::Softmax);

        if (lossType == LossType::MSE) {
             // dL/dA = 2/n * (Pred - Target)
             // dL/dZ = dL/dA * Act'(Z)
             const MatrixR dL_dA = (2.0f / n) * (predictions - targets);
             grad = Math::applyDerivative(layers.back().z_cache, layers.back().a_cache, dL_dA, layers.back().activation);
        }
        else if (lossType == LossType::CrossEntropy && outputIsSoftmax) {
            // Softmax + CrossEntropy combination simplifies to (Pred - Target) / n
            grad = (predictions - targets) / n;
        }
        else if (lossType == LossType::MAE) {
            const MatrixR sign = (predictions - targets).array().sign();
            const MatrixR dL_dA = sign / n;
            grad = Math::applyDerivative(layers.back().z_cache, layers.back().a_cache, dL_dA, layers.back().activation);
        }
        else if (lossType == LossType::Huber) {
            MatrixR diff = predictions - targets;
            MatrixR dL_dA = diff;
            for(int i=0; i<diff.size(); ++i) {
                if (std::abs(diff(i)) <= huberDelta) dL_dA(i) = diff(i);
                else dL_dA(i) = (diff(i) > 0 ? huberDelta : -huberDelta);
            }
            dL_dA /= n;
            grad = Math::applyDerivative(layers.back().z_cache, layers.back().a_cache, dL_dA, layers.back().activation);
        }
        else if (lossType == LossType::MultiHinge) {
            grad = MatrixR::Zero(predictions.rows(), predictions.cols());
            for (int i=0; i<n; ++i) {
                int correctClass;
                targets.row(i).maxCoeff(&correctClass);
                const Scalar correctScore = predictions(i, correctClass);
                int wrongCounts = 0;

                for(int j=0; j<predictions.cols(); ++j) {
                    if (j == correctClass) continue;
                    if (hingeMargin - correctScore + predictions(i, j) > 0) {
                        grad(i, j) = 1.0f / n;
                        wrongCounts++;
                    }
                }
                grad(i, correctClass) = -1.0f * static_cast<float>(wrongCounts) / n;
            }
            // If output is not linear, apply chain rule through activation
             if (layers.back().activation != Activation::None) {
                 grad = Math::applyDerivative(layers.back().z_cache, layers.back().a_cache, grad, layers.back().activation);
             }
        }
        else if (lossType == LossType::ZeroOne) {
            // ZeroOne loss cannot be trained (gradient is 0 everywhere)
            return;
        }

        // 2. Backpropagate through layers
        for (int32_t i = static_cast<int32_t>(layers.size()) - 1; i >= 0; --i) {
            Layer& layer = layers[i];

            // Input to this layer (A_prev)
            const MatrixR& a_prev = (i == 0) ? input : layers[i-1].a_cache;

            // Gradients for Weights and Biases
            // dL/dW = A_prev^T * dL/dZ
            layer.weightsGrad = a_prev.transpose() * grad;

            // dL/dB = sum(dL/dZ) across batch
            layer.biasesGrad = grad.colwise().sum();

            // Propagate Gradient to previous layer (dL/dA_prev)
            // dL/dA_prev = dL/dZ * W^T
            if (i > 0) {
                MatrixR dL_dA_prev = grad * layer.weights.transpose();
                grad = Math::applyDerivative(layers[i-1].z_cache, layers[i-1].a_cache, dL_dA_prev, layers[i-1].activation);
            }
        }
    }

    std::vector<Layer>& getLayers() { return layers; }

    private:
        std::vector<Layer> layers;
        Scalar huberDelta = 1.0f; // Configurable for Huber loss
        Scalar hingeMargin = 1.0f; // Configurable for Hinge loss
    };

}
#endif //ATLAS_FEEDFORWARD_HPP