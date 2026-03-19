
#include "kernels.hpp"
#include "vcl/vectorclass.h"
#include "vcl/vectormath_common.h"


/*
__m256i simd_logical_and_i64(__m256i left, __m256i right) {
    // 1. Create a zero vector to compare against
    const __m256i zero = _mm256_setzero_si256();

    // 2. Compare left and right against zero (creates a mask of -1 where true, 0 where false)
    __m256i left_is_zero = _mm256_cmpeq_epi64(left, zero);
    __m256i right_is_zero = _mm256_cmpeq_epi64(right, zero);

    // 3. Bitwise OR the zero masks (if either was zero, the element is false for logical AND)
    __m256i either_is_zero = _mm256_or_si256(left_is_zero, right_is_zero);

    // 4. Invert the result to get "neither is zero" (i.e., L != 0 && R != 0)
    // We use ANDNOT against a vector of all 1s (which is -1 in two's complement)
    __m256i all_ones = _mm256_set1_epi64x(-1LL);
    return _mm256_andnot_si256(either_is_zero, all_ones);
}
*/

namespace kernels {
    void addi_fp64(const double* src1, const double src2, double* dst, const size_t n) {
        const Vec4d b(src2);
        Vec4d a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4d c = a + b;
            c.store(dst + i);
        }
    }

    void subi_fp64(const double *src1, const double src2, double *dst, const size_t n) {
        const Vec4d b(src2);
        Vec4d a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4d c = a - b;
            c.store(dst + i);
        }
    }

    void isub_fp64(const double src1, const double *src2, double *dst, const size_t n) {
        const Vec4d a(src1);
        Vec4d b;
        for (size_t i = 0; i < n; i += 4) {
            b.load(src2 + i);
            const Vec4d c = a - b;
            c.store(dst + i);
        }
    }

    void muli_fp64(const double *src1, const double src2, double *dst, const size_t n) {
        const Vec4d b(src2);
        Vec4d a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4d c = a * b;
            c.store(dst + i);
        }
    }

    void divi_fp64(const double *src1, const double src2, double *dst, const size_t n) {
        const Vec4d b(src2);
        Vec4d a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4d c = a / b;
            c.store(dst + i);
        }
    }

    void idiv_fp64(const double src1, const double *src2, double *dst, const size_t n) {
        const Vec4d a(src1);
        Vec4d b;
        for (size_t i = 0; i < n; i += 4) {
            b.load(src2 + i);
            const Vec4d c = a / b;
            c.store(dst + i);
        }
    }

    void addi_i64(const int64_t* src1, const int64_t src2, int64_t* dst, const size_t n) {
        const Vec4q b(src2);
        Vec4q a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4q c = a + b;
            c.store(dst + i);
        }
    }
    void subi_i64(const int64_t* src1, const int64_t src2, int64_t* dst, const size_t n) {
        const Vec4q b(src2);
        Vec4q a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4q c = a - b;
            c.store(dst + i);
        }
    }
    void isub_i64(const int64_t src1, const int64_t *src2, int64_t *dst, const size_t n) {
        const Vec4q a(src1);
        Vec4q b;
        for (size_t i = 0; i < n; i += 4) {
            b.load(src2 + i);
            const Vec4q c = a - b;
            c.store(dst + i);
        }
    }
    void muli_i64(const int64_t* src1, const int64_t src2, int64_t* dst, const size_t n) {
        const Vec4q b(src2);
        Vec4q a;
        for (size_t i = 0; i < n; i += 4) {
            a.load(src1 + i);
            const Vec4q c = a * b;
            c.store(dst + i);
        }
    }

    /*
    void store_mask_vcl(Vec4qb mask, int64_t* dest) {
    // OPTION A: Store as -1 (true) and 0 (false)
    // Explicitly cast the boolean vector back to an integer vector
    Vec4q raw_vec = Vec4q(mask);
    raw_vec.store(dest);

    // OPTION B: Store as 1 (true) and 0 (false)
    // Select takes (mask, true_value, false_value)
    Vec4q clean_vec = select(mask, Vec4q(1), Vec4q(0));
    clean_vec.store(dest);
}
     */

}
