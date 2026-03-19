#include "kernels.hpp"
#define HWY_DISABLED_TARGETS (HWY_SSE4 | HWY_SSSE3 | HWY_SSE2)

#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "i64.cpp"
#include <hwy/foreach_target.h>

#include <hwy/highway.h>


HWY_BEFORE_NAMESPACE();

namespace kernels {
    namespace HWY_NAMESPACE {
    namespace hn = hwy::HWY_NAMESPACE;

    HWY_ATTR void add_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Add(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void sub_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Sub(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void mul_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Mul(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void div_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Div(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void divi_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v_out = hn::Div(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void idiv_i64_imp(const int64_t in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, in1);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Div(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void mod_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Mod(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void modi_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
        const auto v2 = hn::Set(d, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v_out = hn::Mod(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void imod_i64_imp(const int64_t in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
        const auto v1 = hn::Set(d, in1);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Mod(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void neg_i64_imp(const int64_t* HWY_RESTRICT in, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Neg(v1);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void abs_i64_imp(const int64_t* HWY_RESTRICT in, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Abs(v1);
            hn::Store(v_out, d, out + i);
        }
    }

    HWY_ATTR void eq_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);

            auto op_mask = hn::Eq(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }
    HWY_ATTR void eqi_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);

            const auto op_mask = hn::Eq(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void neq_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);

            const auto op_mask = hn::Ne(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }
    HWY_ATTR void neqi_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);

            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void lt_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void lti_i64_imp(const int64_t* HWY_RESTRICT src1, int64_t src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, src1 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void ilt_i64_imp(const int64_t src1, const int64_t* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v1 = hn::Set(i64, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(i64, src2 + i);
            const auto op_mask = hn::Lt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void lte_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void ltei_i64_imp(const int64_t* HWY_RESTRICT src1, int64_t src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, src1 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void ilte_i64_imp(const int64_t src1, const int64_t* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v1 = hn::Set(i64, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(i64, src2 + i);
            const auto op_mask = hn::Le(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gt_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gti_i64_imp(const int64_t* HWY_RESTRICT src1, int64_t src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, src1 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void igt_i64_imp(const int64_t src1, const int64_t* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v1 = hn::Set(i64, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(i64, src2 + i);
            const auto op_mask = hn::Gt(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gte_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, in1 + i);
            const auto v2 = hn::Load(i64, in2 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void gtei_i64_imp(const int64_t* HWY_RESTRICT src1, int64_t src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v2 = hn::Set(i64, src2);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(i64, src1 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }

    HWY_ATTR void igte_i64_imp(const int64_t src1, const int64_t* HWY_RESTRICT src2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> i64;
        const size_t lanes = hn::Lanes(i64);
        const auto v1 = hn::Set(i64, src1);
        for (size_t i = 0; i < n; i += lanes) {
            const auto v2 = hn::Load(i64, src2 + i);
            const auto op_mask = hn::Ge(v1, v2);
            const auto v_out_i64 = hn::VecFromMask(i64, op_mask);
            hn::Store(v_out_i64, i64, out + i);
        }
    }
    HWY_ATTR void not_i64_imp(const int64_t* HWY_RESTRICT in, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in + i);
            const auto v_out = hn::Not(v1);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void and_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::And(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void andi_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
            const auto v2 = hn::Set(d, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v_out = hn::And(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void or_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Or(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void ori_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
            const auto v2 = hn::Set(d, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v_out = hn::Or(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void xor_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t* HWY_RESTRICT in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v2 = hn::Load(d, in2 + i);
            const auto v_out = hn::Xor(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
    HWY_ATTR void xori_i64_imp(const int64_t* HWY_RESTRICT in1, const int64_t in2, int64_t* HWY_RESTRICT out, size_t n) {
        constexpr hn::ScalableTag<int64_t> d;
        const size_t lanes = hn::Lanes(d);
            const auto v2 = hn::Set(d, in2);

        for (size_t i = 0; i < n; i += lanes) {
            const auto v1 = hn::Load(d, in1 + i);
            const auto v_out = hn::Xor(v1, v2);
            hn::Store(v_out, d, out + i);
        }
    }
}
}
HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace kernels {
    HWY_EXPORT(add_i64_imp);
    HWY_EXPORT(sub_i64_imp);
    HWY_EXPORT(mul_i64_imp);
    HWY_EXPORT(div_i64_imp);
    HWY_EXPORT(divi_i64_imp);
    HWY_EXPORT(idiv_i64_imp);
    HWY_EXPORT(mod_i64_imp);
    HWY_EXPORT(modi_i64_imp);
    HWY_EXPORT(imod_i64_imp);
    HWY_EXPORT(neg_i64_imp);
    HWY_EXPORT(abs_i64_imp);
    HWY_EXPORT(eq_i64_imp);
    HWY_EXPORT(eqi_i64_imp);
    HWY_EXPORT(neq_i64_imp);
    HWY_EXPORT(neqi_i64_imp);
    HWY_EXPORT(lt_i64_imp);
    HWY_EXPORT(lti_i64_imp);
    HWY_EXPORT(ilt_i64_imp);
    HWY_EXPORT(lte_i64_imp);
    HWY_EXPORT(ltei_i64_imp);
    HWY_EXPORT(ilte_i64_imp);
    HWY_EXPORT(gt_i64_imp);
    HWY_EXPORT(gti_i64_imp);
    HWY_EXPORT(igt_i64_imp);
    HWY_EXPORT(gte_i64_imp);
    HWY_EXPORT(gtei_i64_imp);
    HWY_EXPORT(igte_i64_imp);
    HWY_EXPORT(not_i64_imp);
    HWY_EXPORT(and_i64_imp);
    HWY_EXPORT(andi_i64_imp);
    HWY_EXPORT(or_i64_imp);
    HWY_EXPORT(ori_i64_imp);
    HWY_EXPORT(xor_i64_imp);
    HWY_EXPORT(xori_i64_imp);

    void add_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(add_i64_imp)(src1, src2, dst, n);
    }

    void sub_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(add_i64_imp)(src1, src2, dst, n);
    }

    void mul_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(mul_i64_imp)(src1, src2, dst, n);
    }
    void div_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(div_i64_imp)(src1, src2, dst, n);
    }
    void divi_i64(const int64_t* src1, const int64_t src2, int64_t* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(divi_i64_imp)(src1, src2, dst, n);
    }
    void idiv_i64(const int64_t src1, const int64_t *src2, int64_t *dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(idiv_i64_imp)(src1, src2, dst, n);
    }
    void mod_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(mod_i64_imp)(src1, src2, dst, n);
    }
    void modi_i64(const int64_t* src1, const int64_t src2, int64_t* dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(modi_i64_imp)(src1, src2, dst, n);
    }
    void imod_i64(const int64_t src1, const int64_t *src2, int64_t *dst, const size_t n) {
        return HWY_DYNAMIC_DISPATCH(imod_i64_imp)(src1, src2, dst, n);
    }

    void neg_i64(const int64_t *src, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(abs_i64_imp)(src, dst, n);
    }

    void abs_i64(const int64_t *src, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(abs_i64_imp)(src, dst, n);
    }

    void eq_i64(const int64_t *src1, const int64_t* src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(eq_i64_imp)(src1, src2, dst, n);
    }

    void eqi_i64(const int64_t *src1, int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(eqi_i64_imp)(src1, src2, dst, n);
    }

    void neq_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(neq_i64_imp)(src1, src2, dst, n);
    }
    void neqi_i64(const int64_t *src1, int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(neqi_i64_imp)(src1, src2, dst, n);
    }

    void lt_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lt_i64_imp)(src1, src2, dst, n);
    }

    void lti_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lti_i64_imp)(src1, src2, dst, n);
    }

    void ilt_i64(int64_t src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ilt_i64_imp)(src1, src2, dst, n);
    }

    void lte_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(lte_i64_imp)(src1, src2, dst, n);
    }

    void ltei_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ltei_i64_imp)(src1, src2, dst, n);
    }

    void ilte_i64(int64_t src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ilte_i64_imp)(src1, src2, dst, n);
    }

    void gt_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gt_i64_imp)(src1, src2, dst, n);
    }

    void gti_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gti_i64_imp)(src1, src2, dst, n);
    }

    void igt_i64(int64_t src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(igt_i64_imp)(src1, src2, dst, n);
    }

    void gte_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gte_i64_imp)(src1, src2, dst, n);
    }

    void gtei_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(gtei_i64_imp)(src1, src2, dst, n);
    }

    void igte_i64(int64_t src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(igte_i64_imp)(src1, src2, dst, n);
    }

    void not_i64(const int64_t *src, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(not_i64_imp)(src, dst, n);
    }

    void and_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(and_i64_imp)(src1, src2, dst, n);
    }
    void andi_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(andi_i64_imp)(src1, src2, dst, n);
    }
    void or_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(or_i64_imp)(src1, src2, dst, n);
    }
    void ori_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(ori_i64_imp)(src1, src2, dst, n);
    }
    void xor_i64(const int64_t *src1, const int64_t *src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(xor_i64_imp)(src1, src2, dst, n);
    }
    void xori_i64(const int64_t *src1, const int64_t src2, int64_t *dst, size_t n) {
        return HWY_DYNAMIC_DISPATCH(xori_i64_imp)(src1, src2, dst, n);
    }
}
#endif // HWY_ONCE