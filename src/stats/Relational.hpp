#pragma once

#include "Common.hpp"
#include "Descriptive.hpp"
#include <vector>

namespace stats {
    double covariance(const double* X, const double* Y, size_t n) {
        double sum_x = 0.0, sum_y = 0.0;
        double sum_x2 = 0.0, sum_y2 = 0.0;
        double sum_xy = 0.0;

        // Single pass cov
        for (int i = 0; i < n; ++i) {
            sum_x += X[i];
            sum_y += Y[i];
            sum_x2 += X[i] * X[i];
            sum_y2 += Y[i] * Y[i];
            sum_xy += X[i] * Y[i];
        }

        return n * sum_xy - sum_x * sum_y;
    }

    double pearson_corr(const double* X, const double* Y, size_t n) {
        if (n <= 1) return 0.0; // Undefined for n < 2

        double sum_x = 0.0, sum_y = 0.0;
        double sum_x2 = 0.0, sum_y2 = 0.0;
        double sum_xy = 0.0;

        // Single pass pearson
        for (int i = 0; i < n; ++i) {
            sum_x += X[i];
            sum_y += Y[i];
            sum_x2 += X[i] * X[i];
            sum_y2 += Y[i] * Y[i];
            sum_xy += X[i] * Y[i];
        }

        double numerator = n * sum_xy - sum_x * sum_y;
        double denom_x = n * sum_x2 - sum_x * sum_x;
        double denom_y = n * sum_y2 - sum_y * sum_y;

        if (denom_x == 0 || denom_y == 0) return 0.0;

        return numerator / std::sqrt(denom_x * denom_y);
    }


    template<typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] std::vector<double> get_ranks(const T* data, size_t n) {
        std::vector<size_t> indices(n);
        // Fill indices with 0, 1, ..., n-1
        std::iota(indices.begin(), indices.end(), 0);

        // Sort indices based on the values in the data array
        std::sort(indices.begin(), indices.end(), [data](int a, int b) {
            return data[a] < data[b];
            });

        std::vector<double> ranks(n);

        for (int i = 0; i < n; ) {
            int j = i + 1;

            // Detect ties: advance j while values are equal
            while (j < n && (std::abs(data[indices[j]] - data[indices[i]]) < 1e-9)) {
                j++;
            }

            // Calculate the average rank for the tied group
            // The positions are (i+1) to j. Average is (i + 1 + j) / 2.0
            double avg_rank = (double)(i + 1 + j) / 2.0;

            // Assign this average rank to all indices in the current group
            for (int k = i; k < j; ++k) {
                ranks[indices[k]] = avg_rank;
            }

            // Move to the next group
            i = j;
        }

        return ranks;
    }

    template<typename T>
        requires std::is_arithmetic_v<T>
    double spearman_corr(const T* X, const T* Y, int n) {
        if (n <= 1) return 0.0; // Undefined for n < 2

        std::vector<double> rankX = get_ranks(X, n);
        std::vector<double> rankY = get_ranks(Y, n);

        double sum_x = 0.0, sum_y = 0.0;
        double sum_x2 = 0.0, sum_y2 = 0.0;
        double sum_xy = 0.0;

        // Use a single pass to compute pearson corr
        for (int i = 0; i < n; ++i) {
            sum_x += rankX[i];
            sum_y += rankY[i];
            sum_x2 += rankX[i] * rankX[i];
            sum_y2 += rankY[i] * rankY[i];
            sum_xy += rankX[i] * rankY[i];
        }

        double numerator = n * sum_xy - sum_x * sum_y;
        double denom_x = n * sum_x2 - sum_x * sum_x;
        double denom_y = n * sum_y2 - sum_y * sum_y;

        if (denom_x == 0 || denom_y == 0) return 0.0; // Avoid division by zero

        return numerator / std::sqrt(denom_x * denom_y);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    double spearman_corr_stable(const T* X, const T* Y, int n) {
        if (n <= 1) return 0.0;

        std::vector<double> rankX = get_ranks(X, n);
        std::vector<double> rankY = get_ranks(Y, n);

        double mean_x = 0.0;
        double mean_y = 0.0;
        double m2_x = 0.0; // Sum of squares of differences from the mean for X
        double m2_y = 0.0; // Sum of squares of differences from the mean for Y
        double cov_xy = 0.0; // Co-moment (numerator component)

        for (int i = 0; i < n; ++i) {
            double x = rankX[i];
            double y = rankY[i];

            // Update Mean X and M2_X
            double delta_x = x - mean_x;
            mean_x += delta_x / (i + 1);
            m2_x += delta_x * (x - mean_x);

            // Update Mean Y and M2_Y
            double delta_y = y - mean_y;
            mean_y += delta_y / (i + 1);
            m2_y += delta_y * (y - mean_y);

            // Update Covariance term
            // Note: Use delta_x (diff from OLD mean) and (y - mean_y) (diff from NEW mean)
            cov_xy += delta_x * (y - mean_y);
        }

        // Mathematical checks to prevent NaN on constant inputs
        if (m2_x == 0.0 || m2_y == 0.0) return 0.0;

        return cov_xy / std::sqrt(m2_x * m2_y);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    double spearman_corr_centered(const T* X, const T* Y, int n) {
        if (n <= 1) return 0.0;

        std::vector<double> rankX = get_ranks(X, n);
        std::vector<double> rankY = get_ranks(Y, n);

        // We know the mean of ranks is exactly (N + 1) / 2
        double expected_mean = static_cast<double>(n + 1) / 2.0;

        double sum_sq_x = 0.0;
        double sum_sq_y = 0.0;
        double sum_cov = 0.0;

        // This loop vectorizes very well (SIMD friendly)
        for (int i = 0; i < n; ++i) {
            double d_x = rankX[i] - expected_mean;
            double d_y = rankY[i] - expected_mean;

            sum_sq_x += d_x * d_x;
            sum_sq_y += d_y * d_y;
            sum_cov += d_x * d_y;
        }

        // Note: If ranks are tied, the actual mean might drift slightly from expected_mean,
        // but for correlation math, centering by a constant is valid and stable.
        // However, for perfect Pearson strictness on tied data, we should ideally use the 
        // real calculated mean if we want to be pedantic, but for ranks, 
        // the drift is usually negligible unless ties are massive.

        // To be 100% safe against massive ties affecting the mean:
        // It's safer to re-calculate the exact mean if you have heavy ties.
        // But since the sum of ranks is invariant even with ties, 
        // expected_mean == actual_mean is ALWAYS TRUE for ranks!
        // Proof: Sum of ranks 1..N is N(N+1)/2. Ties just average them, sum stays same.
        // So expected_mean is always correct.

        if (sum_sq_x == 0.0 || sum_sq_y == 0.0) return 0.0;

        return sum_cov / std::sqrt(sum_sq_x * sum_sq_y);
    }

    double r2(const double* predictions, const double* actual, size_t n) {
        double ssr = 0.0;
        double sst = variance(actual, n, Scope::Population) * static_cast<double>(n);

        for (size_t i = 0; i < n; i++)
        {
            ssr += (actual[i] - predictions[i]) * (actual[i] - predictions[i]);
        }

        return 1.0 - (ssr / sst);
    }

    double adjusted_r2(const double* predictions, const double* actual, size_t n, size_t n_estimators) {
        double ssr = 0.0;
        double sst = variance(actual, n, Scope::Population) * static_cast<double>(n);
        double dfres = n - n_estimators - 1.0;
        double dftot = n - 1.0;

        for (size_t i = 0; i < n; i++)
        {
            ssr += (actual[i] - predictions[i]) * (actual[i] - predictions[i]);
        }
        ssr /= dfres;
        sst /= dftot;
        return 1.0 - (ssr / sst);
    }

    // Standard auto correlation function
    // Parameters: 
    // data: pointer to the data
    // n: length of the data array
    // lag: lag parameter
    double acf(const double* data, size_t n, size_t lag) {

        if (lag >= n) return 0.0;
        if (lag == 0) return 1.0; // Correlation with self is always 1

        double mean = stats::mean(data, n);
        double ss_total = stats::variance(data, n, Scope::Population) * static_cast<double>(n);

        if (ss_total <= 10e-9) return 0.0;

        double ss_cov = 0.0;
        size_t limit = n - lag;

        for (size_t i = 0; i < limit; ++i) {
            double diff_t = data[i] - mean;
            double diff_t_k = data[i + lag] - mean; // The future value

            ss_cov += diff_t * diff_t_k;
        }

        // Standard ACF normalized by ss_total
        return ss_cov / ss_total;
    }

    [[nodiscard]] std::vector<double> pacf(const double* data, size_t n, size_t n_lags) {
        if (n_lags == 0) return {};

        std::vector<double> acf(n_lags);

        for (size_t i = 0; i < n_lags; i++)
        {
            acf[i] = stats::acf(data, n, i);
        }

        std::vector<double> phi(n_lags); // The PACF results

        // At lag 0, PACF is always 1.0 (correlation with itself)
        phi[0] = 1.0;

        if (n_lags == 1) return phi;

        // Temporary buffers for AR coefficients
        // We need to store the coefficients of the AR model at step (k-1)
        // to compute step (k).
        std::vector<double> ar_coeffs;
        ar_coeffs.reserve(n_lags);

        // --- Step k=1 (Base Case) ---
        // PACF(1) is just ACF(1)
        phi[1] = acf[1];
        ar_coeffs.push_back(acf[1]); // AR(1) coefficient is just rho_1

        // --- Step k=2 to n_lags-1 ---
        for (size_t k = 2; k < n_lags; ++k) {

            // 1. Compute the numerator and denominator for the next phi (reflection coeff)
            // Numerator = rho_k - sum( ar_coeff[j] * rho_{k-1-j} )
            double numerator = acf[k];
            double denominator = 1.0;

            for (size_t j = 0; j < k - 1; ++j) {
                // Note: 'ar_coeffs' currently holds coefficients for order (k-1)
                double rho_term = acf[k - 1 - j];
                numerator -= ar_coeffs[j] * rho_term;

                // Denominator uses the same sum structure but with 'reverse' rho
                // Or simply: 1 - sum(alpha_j * rho_j)
                denominator -= ar_coeffs[j] * acf[j + 1];
            }

            // 2. Compute the k-th PACF value
            // Guard against division by zero (perfect correlation)
            if (std::abs(denominator) < 1e-9) {
                phi[k] = 0.0;
            }
            else {
                phi[k] = numerator / denominator;
            }

            // 3. Update the AR coefficients for the NEXT iteration
            // The Durbin-Levinson recursion:
            // a_new[j] = a_old[j] - phi[k] * a_old[k-1-j]

            auto new_coeffs = ar_coeffs; // Copy old coeffs
            new_coeffs.push_back(phi[k]); // The new k-th coeff is the PACF itself

            for (size_t j = 0; j < k - 1; ++j) {
                new_coeffs[j] = ar_coeffs[j] - phi[k] * ar_coeffs[k - 2 - j];
            }

            ar_coeffs = std::move(new_coeffs);
        }

        return phi;
    }
}