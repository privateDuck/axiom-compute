#pragma once

#include "Common.hpp"
#include <vector>

namespace stats {

    template<typename T>
    [[nodiscard]] inline double mean(std::span<T> data) {
        if (data.size() == 0) return 0.0; // Empty

        double sum = 0.0;
        for (const auto x : data) {
            sum += static_cast<double>(x);
        }

        return sum / static_cast<double>(data.size());
    }

    template<typename T>
    [[nodiscard]] inline auto variance(std::span<T> data, Scope scope = Scope::Sample) {
        double mu = mean(data);
        double sum = 0.0;
        for (const auto x : data) {
            double diff = static_cast<double>(x)-mu;
            sum += diff * diff;
        }

        double denom = (scope == Scope::Sample) ? (data.size() - 1.0) : static_cast<double>(data.size());
        return sum / denom;
    }

    inline double mean(const double* data, size_t n) {
        double mu = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mu += data[i];
        }
        return mu /= static_cast<double>(n);
    }

   inline double variance(const double* data, size_t n, Scope scope = Scope::Sample) {
        double mu = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mu += data[i];
        }
        mu /= static_cast<double>(n);

        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mu;
            sum += diff * diff;
        }

        double denom = (scope == Scope::Sample) ? (n - 1.0) : static_cast<double>(n);
        return sum / denom;
    }

    inline double stddev(const double* data, size_t n, Scope scope = Scope::Sample) {
        double mu = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mu += data[i];
        }
        mu /= static_cast<double>(n);

        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mu;
            sum += diff * diff;
        }

        double denom = (scope == Scope::Sample) ? (n - 1.0) : static_cast<double>(n);
        return std::sqrt(sum / denom);
    }

    inline void var_and_stddev(const double* data, size_t n, double& var_out, double& std_out, Scope scope = Scope::Sample) {
        double mu = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mu += data[i];
        }
        mu /= static_cast<double>(n);

        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mu;
            sum += diff * diff;
        }

        double denom = (scope == Scope::Sample) ? (n - 1.0) : static_cast<double>(n);
        var_out = (sum / denom);
        std_out = std::sqrt(var_out);
    }

    inline void quantiles(const double* data, size_t n, double& q1, double& q2, double& q3) {
        std::vector<double> cpy(data, data + n);
        //std::memcpy(cpy.data(), data, sizeof(double) * n);
        std::sort(cpy.begin(), cpy.end());
        size_t q1n = static_cast<size_t>(((n + 1) / 4));
        size_t q2n = static_cast<size_t>(((n + 1) / 2));
        size_t q3n = static_cast<size_t>((3 * (n + 1) / 4));
        q1 = cpy[q1n];
        q2 = cpy[q2n];
        q3 = cpy[q3n];
    }

    inline double skewness(const double* data, size_t n) {

        double m = data[0];
        double s2m = 0.0;
        double s3m = 0.0;

        for (size_t i = 1; i < n; i++)
        {
            auto nc = static_cast<double>(i);
            const double recipN = 1.0 / nc;

            double delta = data[i] - m;
            m += delta * recipN;
            double deltaN = data[i] - m;
            double ddN = delta * deltaN;
            s2m += ddN;
            s3m += ddN + (delta + deltaN) - (3.0 * ddN * (nc - 1.0) * recipN);
        }

        return std::sqrt(static_cast<double>(n) * (n - 1.0)) * s3m / ((n - 2.0) * std::pow(s2m, 1.5));
    }

    inline double kurtosis(const double* data, size_t n) {
        double mean = 0.0;
        double m2 = 0.0;
        double m3 = 0.0;
        double m4 = 0.0;

        for (size_t i = 1; i < n; i++)
        {
            auto nc = static_cast<double>(i);
            double n1 = nc - 1.0;
            double recipN = 1.0 / nc;

            double delta = data[i] - mean;
            mean += delta * recipN;
            double deltaN = delta * recipN;
            double deltaN2 = deltaN * deltaN;
            double t1 = delta * deltaN * n1;
            m4 += t1 * deltaN2 * (nc * nc - 3.0 * nc + 3.0) + 6.0 * deltaN2 * m2 - 4.0 * deltaN * m3;
            m3 += t1 * deltaN * (n - 2.0) - 3.0 * deltaN * m2;
            m2 += t1;
        }

        return (n * m4 / (m2 * m2)) - 3.0;
    }

    inline double standard_error(const double* data, size_t n) {
        const double var = variance(data, n);
        return std::sqrt(var / n);
    }
}