

#include "kernels.hpp"

#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "fp_64.cpp"
#include <hwy/foreach_target.h>

#include <hwy/highway.h>
#include <hwy/contrib/math/math-inl.h>


HWY_BEFORE_NAMESPACE();

namespace kernels {
namespace HWY_NAMESPACE {
    namespace hn = hwy::HWY_NAMESPACE;

    HWY_ATTR void add_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Add(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void sub_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Sub(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void fma_fp64_imp(const double* HWY_RESTRICT a, const double* HWY_RESTRICT b, const double* HWY_RESTRICT c, double* HWY_RESTRICT out, const size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, a + i);
            const auto v2 = hn::Load(d, b + i);
            auto v3 = hn::Load(d, c + i);
            v3 = hn::MulAdd(v1, v2, v3);
            hn::Store(v3, d, out + i);
        }
    }

    HWY_ATTR void nfma_fp64_imp(const double* HWY_RESTRICT a, const double* HWY_RESTRICT b, const double* HWY_RESTRICT c, double* HWY_RESTRICT out, const size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, a + i);
            const auto v2 = hn::Load(d, b + i);
            auto v3 = hn::Load(d, c + i);
            v3 = hn::NegMulAdd(v1, v2, v3);
            hn::Store(v3, d, out + i);
        }
    }

    HWY_ATTR void fmsub_fp64_imp(const double* HWY_RESTRICT a, const double* HWY_RESTRICT b, const double* HWY_RESTRICT c, double* HWY_RESTRICT out, const size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, a + i);
            const auto v2 = hn::Load(d, b + i);
            auto v3 = hn::Load(d, c + i);
            v3 = hn::MulSub(v1, v2, v3);
            hn::Store(v3, d, out + i);
        }
    }

    HWY_ATTR void nfmsub_fp64_imp(const double* HWY_RESTRICT a, const double* HWY_RESTRICT b, const double* HWY_RESTRICT c, double* HWY_RESTRICT out, const size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, a + i);
            const auto v2 = hn::Load(d, b + i);
            auto v3 = hn::Load(d, c + i);
            v3 = hn::NegMulSub(v1, v2, v3);
            hn::Store(v3, d, out + i);
        }
    }

    HWY_ATTR void neg_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Neg(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void sqrt_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Sqrt(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void abs_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Abs(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void eq_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto vcomp = hn::Set(d, REAL_EQUAL_THRESHOLD);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);

            // We check for |in2 - in1| < eps
            auto cond = hn::Sub(v1, v2);
            cond = hn::Abs(cond);
            const auto op_mask = hn::Lt(cond, vcomp);

            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }
    HWY_ATTR void eqi_fp64_imp(const double* HWY_RESTRICT in1, const double in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, in2);
        const auto vcomp = hn::Set(d, REAL_EQUAL_THRESHOLD);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);

            // We check for |in2 - in1| < eps
            auto cond = hn::Sub(v1, v2);
            cond = hn::Abs(cond);
            const auto op_mask = hn::Lt(cond, vcomp);

            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void neq_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto vcomp = hn::Set(d, REAL_EQUAL_THRESHOLD);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);

            // We check for |in2 - in1| > eps
            auto cond = hn::Sub(v1, v2);
            cond = hn::Abs(cond);
            const auto op_mask = hn::Gt(cond, vcomp);

            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }
    HWY_ATTR void neqi_fp64_imp(const double* HWY_RESTRICT in1, const double in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, in2);
        const auto vcomp = hn::Set(d, REAL_EQUAL_THRESHOLD);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);

            // We check for |in2 - in1| > eps
            auto cond = hn::Sub(v1, v2);
            cond = hn::Abs(cond);
            const auto op_mask = hn::Gt(cond, vcomp);

            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void lt_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void lti_fp64_imp(const double* HWY_RESTRICT src1, double src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, src1 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void ilt_fp64_imp(const double src1, const double* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, src2 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void lte_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void ltei_fp64_imp(const double* HWY_RESTRICT src1, double src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, src1 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void ilte_fp64_imp(const double src1, const double* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, src2 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gt_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void gti_fp64_imp(const double* HWY_RESTRICT src1, double src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, src1 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void igt_fp64_imp(const double src1, const double* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, src2 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gte_fp64_imp(const double* HWY_RESTRICT in1, const double* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void gtei_fp64_imp(const double* HWY_RESTRICT src1, double src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, src1 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    void igte_fp64_imp(const double src1, const double* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, src2 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_f64 = hn::VecFromMask(d, op_mask);
            const auto v_out_i64 = hn::BitCast(i64, v_out_f64);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void sign_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::CopySign(hn::Set(d, 1.0), v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void log_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Log(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void log2_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Log2(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void log10_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Log10(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void exp_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Exp(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void floor_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Floor(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void ceil_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Ceil(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void round_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Round(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void sin_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Sin(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void cos_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Cos(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void tan_fp64_imp(const double* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        const size_t lanes = hn::Lanes(d);
        using D = hn::ScalableTag<double>;

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            hn::Vec<D> vs;
            hn::Vec<D> vc;
            hn::SinCos(d, v1, vs, vc);
            const auto v_out = hn::Div(vs, vc);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void cast_f64_i64_imp(const double* HWY_RESTRICT in, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::ConvertTo(i64, v1);
            hn::Store(v_out, i64, out + i);
        }
    }

    HWY_ATTR void cast_i64_f64_imp(const int64_t* HWY_RESTRICT in, double* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<double> d;
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in + i);
            const auto v_out = hn::ConvertTo(d, v1);
            hn::Store(v_out, d, out + i);
        }
    }
}
}
HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace kernels {

    HWY_EXPORT(add_fp64_imp);
    HWY_EXPORT(sub_fp64_imp);
    HWY_EXPORT(fma_fp64_imp);
    HWY_EXPORT(nfma_fp64_imp);
    HWY_EXPORT(fmsub_fp64_imp);
    HWY_EXPORT(nfmsub_fp64_imp);
    HWY_EXPORT(neg_fp64_imp);
    HWY_EXPORT(sqrt_fp64_imp);
    HWY_EXPORT(abs_fp64_imp);
    HWY_EXPORT(eq_fp64_imp);
    HWY_EXPORT(eqi_fp64_imp);
    HWY_EXPORT(neq_fp64_imp);
    HWY_EXPORT(neqi_fp64_imp);
    HWY_EXPORT(lt_fp64_imp);
    HWY_EXPORT(lti_fp64_imp);
    HWY_EXPORT(ilt_fp64_imp);
    HWY_EXPORT(lte_fp64_imp);
    HWY_EXPORT(ltei_fp64_imp);
    HWY_EXPORT(ilte_fp64_imp);
    HWY_EXPORT(gt_fp64_imp);
    HWY_EXPORT(gti_fp64_imp);
    HWY_EXPORT(igt_fp64_imp);
    HWY_EXPORT(gte_fp64_imp);
    HWY_EXPORT(gtei_fp64_imp);
    HWY_EXPORT(igte_fp64_imp);
    HWY_EXPORT(sign_fp64_imp);
    HWY_EXPORT(log_fp64_imp);
    HWY_EXPORT(log2_fp64_imp);
    HWY_EXPORT(log10_fp64_imp);
    HWY_EXPORT(exp_fp64_imp);
    HWY_EXPORT(floor_fp64_imp);
    HWY_EXPORT(ceil_fp64_imp);
    HWY_EXPORT(round_fp64_imp);
    HWY_EXPORT(sin_fp64_imp);
    HWY_EXPORT(cos_fp64_imp);
    HWY_EXPORT(tan_fp64_imp);
    HWY_EXPORT(cast_f64_i64_imp);
    HWY_EXPORT(cast_i64_f64_imp);

    void add_fp64(const double* src1, const double* src2, double* dst, size_t n) {
        // Route the call to the best CPU instruction set
        return HWY_DYNAMIC_DISPATCH(add_fp64_imp)(src1, src2, dst, n);
    }

    void sub_fp64(const double* src1, const double* src2, double* dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(sub_fp64_imp)(src1, src2, dst, n);
    }

    void fma_fp64(const double* a, const double* b, const double* c, double* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(fma_fp64_imp)(a, b, c, dst, n);
    }

    void nfma_fp64(const double* a, const double* b, const double* c, double* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(nfma_fp64_imp)(a, b, c, dst, n);
    }

    void fmsub_fp64(const double* a, const double* b, const double* c, double* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(fmsub_fp64_imp)(a, b, c, dst, n);
    }

    void nfmsub_fp64(const double* a, const double* b, const double* c, double* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(nfmsub_fp64_imp)(a, b, c, dst, n);
    }

    void neg_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(neg_fp64_imp)(src, dst, n);
    }

    void sqrt_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(sqrt_fp64_imp)(src, dst, n);
    }

    void abs_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(abs_fp64_imp)(src, dst, n);
    }

    void eq_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(eq_fp64_imp)(src1, src2, dst, n);
    }

    void eqi_fp64(const double *src1, double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(eqi_fp64_imp)(src1, src2, dst, n);
    }

    void neq_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(neq_fp64_imp)(src1, src2, dst, n);
    }
    void neqi_fp64(const double *src1, double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(neqi_fp64_imp)(src1, src2, dst, n);
    }

    void lt_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lt_fp64_imp)(src1, src2, dst, n);
    }

    void lti_fp64(const double *src1, const double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lti_fp64_imp)(src1, src2, dst, n);
    }

    void ilt_fp64(double src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ilt_fp64_imp)(src1, src2, dst, n);
    }

    void lte_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lte_fp64_imp)(src1, src2, dst, n);
    }

    void ltei_fp64(const double *src1, const double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ltei_fp64_imp)(src1, src2, dst, n);
    }

    void ilte_fp64(double src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ilte_fp64_imp)(src1, src2, dst, n);
    }

    void gt_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gt_fp64_imp)(src1, src2, dst, n);
    }

    void gti_fp64(const double *src1, const double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gti_fp64_imp)(src1, src2, dst, n);
    }

    void igt_fp64(double src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(igt_fp64_imp)(src1, src2, dst, n);
    }

    void gte_fp64(const double *src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gte_fp64_imp)(src1, src2, dst, n);
    }

    void gtei_fp64(const double *src1, const double src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gtei_fp64_imp)(src1, src2, dst, n);
    }

    void igte_fp64(double src1, const double *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(igte_fp64_imp)(src1, src2, dst, n);
    }

    void sign_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(sign_fp64_imp)(src, dst, n);
    }

    void log_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(log_fp64_imp)(src, dst, n);
    }

    void log2_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(log2_fp64_imp)(src, dst, n);
    }

    void log10_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(log10_fp64_imp)(src, dst, n);
    }

    void exp_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(exp_fp64_imp)(src, dst, n);
    }

    void floor_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(floor_fp64_imp)(src, dst, n);
    }

    void ceil_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ceil_fp64_imp)(src, dst, n);
    }

    void round_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(round_fp64_imp)(src, dst, n);
    }

    void sin_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(sin_fp64_imp)(src, dst, n);
    }

    void cos_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(cos_fp64_imp)(src, dst, n);
    }

    void tan_fp64(const double *src, double *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(tan_fp64_imp)(src, dst, n);
    }

    void cast_f64_i64(const double* src, int64_t* dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(cast_f64_i64_imp)(src, dst, n);
    }

    void cast_i64_f64(const int64_t* src, double* dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(cast_i64_f64_imp)(src, dst, n);
    }
}
#endif // HWY_ONCE
