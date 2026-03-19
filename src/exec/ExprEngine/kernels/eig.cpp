#include "kernels.hpp"
#include <Eigen/Dense>

namespace kernels {

    double standardNormalCDF(const double x) {
        return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
    }

    void pow_fp64(double *src1, double *src2, double *dst, const size_t n) {
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> a(src1, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> b(src2, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> c(dst, n);

        c.array() = a.array().pow(b.array());
    }

    void ipow_fp64(const double src1, double *src2, double *dst, const size_t n) {
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> b(src2, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> c(dst, n);

        c.array() = Eigen::VectorXd::Constant(n, src1).array().pow(b.array());
    }

    void powi_fp64(double* src1, const double src2, double *dst, const size_t n) {
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> a(src1, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> c(dst, n);

        c.array() = a.array().pow(Eigen::VectorXd::Constant(n, src2).array());
    }

    void erf_fp64(double *src, double *dst, const size_t n) {
        const Eigen::Map<Eigen::VectorXd, Eigen::Aligned> a(src, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> c(dst, n);

        c.noalias() = a.unaryExpr([](const double x) { return std::erf(x); });
    }

    void cdfnorm_fp64(double *src, double *dst, const size_t n) {
        const Eigen::Map<Eigen::VectorXd, Eigen::Aligned> a(src, n);
        Eigen::Map<Eigen::VectorXd, Eigen::Aligned> c(dst, n);

        c.noalias() = a.unaryExpr([](const double x) { return standardNormalCDF(x); });
    }
}