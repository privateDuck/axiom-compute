#pragma once

#include <armadillo>
#include <Eigen/Eigen>
#include <unordered_map>
#include <variant>

enum class RegressionMetric {
	MSE,
	MAE,
	RMSE,
	R2
};

enum class RegressionLoss {
    MAE,
    MSE,
	L1Smooth,
	Huber,
    RMSE
};

enum class ClassificationMetric {
    Accuracy,
    F1Score,
    Precision,
    Recall,
    AUCROC
};

enum class ClassificationLoss {
    CrossEntropy,
    Hinge,
    SquaredHinge,
    NegativeLogLikelihood,
    KLDivergence
};


using Matrix = Eigen::MatrixXd;
using Vector = Eigen::VectorXd;


struct RegressionPrediction {
    Vector predictions;

    double ComputeMetric(const Vector& true_values, const RegressionMetric metric) const;
};


struct ClassificationPrediction {
    Matrix class_probabilities; // Each row corresponds to a sample, each column to a class
    Vector predicted_classes; // Predicted class labels for each sample
    double ComputeMetric(const Vector& true_labels, const ClassificationMetric metric) const;
};


using InferenceResult = std::variant<RegressionPrediction, ClassificationPrediction>;
using ParameterSet = std::unordered_map<std::string, double>;


// Eigen Arma Mappings
// Mutable: Eigen -> Armadillo
template <typename Derived>
inline auto view_as_arma(Eigen::PlainObjectBase<Derived>& eigen_m) {
    using Scalar = typename Derived::Scalar;

    return arma::Mat<Scalar>(
        eigen_m.data(),
        eigen_m.rows(),
        eigen_m.cols(),
        false,
        true
    );
}

// Immutable: Eigen -> Armadillo
template <typename Derived>
inline const auto view_as_arma(const Eigen::PlainObjectBase<Derived>& eigen_m) {
    using Scalar = typename Derived::Scalar;

    // We must const_cast the pointer because Armadillo's constructor 
    // strictly requires a non-const pointer for views.
    // However, by returning const arma::Mat, we enforce read only usage.
    Scalar* safe_ptr = const_cast<Scalar*>(eigen_m.data());

    return arma::Mat<Scalar>(
        safe_ptr,
        eigen_m.rows(),
        eigen_m.cols(),
        false,
        true
    );
}

// MUTABLE: Armadillo -> Eigen
template <typename Scalar>
inline auto view_as_eigen(arma::Mat<Scalar>& arma_m) {
    return Eigen::Map<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>(
        arma_m.memptr(),
        arma_m.n_rows,
        arma_m.n_cols
    );
}