#pragma once

#include <torch/torch.h>
#include <cmath>
#include <stdexcept>

class MultivariateNormal {
private:
    torch::Tensor loc;
    torch::Tensor scale_tril; // Lower triangular matrix L such that Sigma = L * L^T

public:
    // Constructor: Supports initialization via covariance matrix
    MultivariateNormal(const torch::Tensor& loc, const torch::Tensor& covariance_matrix) {
        if (loc.dim() < 1) {
            throw std::invalid_argument("loc must be at least 1D");
        }

        // Handle broadcasting of loc and covariance if necessary
        // In a full library, you would use strict broadcasting checks here.
        this->loc = loc;

        // Compute Cholesky decomposition: Sigma = L * L^T
        // Corresponds to: self._unbroadcasted_scale_tril = torch.linalg.cholesky(covariance_matrix)
       
        this->scale_tril = torch::linalg_cholesky(covariance_matrix);
    }

    // Alternative Constructor: Initialize directly with scale_tril (L) for efficiency
    static MultivariateNormal from_scale_tril(const torch::Tensor& loc, const torch::Tensor& scale_tril) {
        // Create a dummy object and populate it manually
        // (Alternatively, make constructors protected and use a builder pattern)
        MultivariateNormal dist(loc, torch::eye(loc.size(-1)));
        dist.scale_tril = scale_tril;
        return dist;
    }

    // Corresponds to: rsample()
    torch::Tensor rsample(c10::IntArrayRef sample_shape = {}) {
        // 1. Create standard normal noise: epsilon ~ N(0, I)
        auto shape = sample_shape.vec();

        // Append the shape of the location (batch_shape + event_shape)
        shape.insert(shape.end(), loc.sizes().begin(), loc.sizes().end());

        torch::Tensor eps = torch::randn(shape, loc.options());

        // 2. Reparameterize: x = loc + L * epsilon
        // We use matmul. Note: eps needs to be treated as a column vector for the multiplication
        // equivalent to _batch_mv in your python code
        auto res = this->loc + torch::matmul(this->scale_tril, eps.unsqueeze(-1)).squeeze(-1);
        return res;
    }

    // Corresponds to: log_prob(value)
    torch::Tensor log_prob(const torch::Tensor& value) {
        auto diff = value - this->loc;

        // Mahalanobis distance calculation:
        // We want (x - mu)^T * Sigma^-1 * (x - mu)
        // Since Sigma = L * L^T, this is || L^-1 * (x - mu) ||^2

        // Solve L * y = (x - mu) for y. 
        // 'upper=false' specifies L is lower triangular.
        auto M_swap = torch::linalg_solve_triangular(this->scale_tril, diff.unsqueeze(-1), /*upper=*/false);

        // Compute squared norm along the last dimension
        auto M = M_swap.squeeze(-1).pow(2).sum(-1);

        // Log determinant of Sigma = 2 * sum(log(diag(L)))
        auto half_log_det = this->scale_tril.diagonal(/*offset=*/0, /*dim1=*/-2, /*dim2=*/-1).log().sum(-1);

        auto event_shape = this->loc.size(-1);
        double log_2pi = std::log(2 * M_PI);

        // log probability
        return -0.5 * (event_shape * log_2pi + M) - half_log_det;
    }

    // Helper to retrieve the covariance matrix if needed (reconstructed from L)
    torch::Tensor covariance_matrix() const {
        return torch::matmul(scale_tril, scale_tril.transpose(-1, -2));
    }
};