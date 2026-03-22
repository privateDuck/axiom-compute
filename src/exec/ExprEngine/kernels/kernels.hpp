#pragma once
#include <cstdint>

namespace kernels {
    static constexpr double REAL_EQUAL_THRESHOLD = 0.000001;
    void add_fp64(const double* src1, const double* src2, double* dst, size_t n);
    void addi_fp64(const double* src1, double src2, double* dst, size_t n);

    void sub_fp64(const double* src1, const double* src2, double* dst, size_t n);
    void subi_fp64(const double* src1, double src2, double* dst, size_t n);
    void isub_fp64(double src1, const double* src2, double* dst, size_t n);

    void mul_fp64(const double* src1, const double* src2, double* dst, size_t n);
    void muli_fp64(const double* src1, double src2, double* dst, size_t n);

    void div_fp64(const double* src1, const double* src2, double* dst, size_t n);
    void divi_fp64(const double* src1, double src2, double* dst, size_t n);
    void idiv_fp64(double src1, const double* src2, double* dst, size_t n);

    // dst = (a * b) + c
    void fma_fp64(const double* a, const double* b, const double* c, double* dst, size_t n);
    // dst = -(a * b) + c
    void nfma_fp64(const double* a, const double* b, const double* c, double* dst, size_t n);
    // dst = (a * b) - c
    void fmsub_fp64(const double* a, const double* b, const double* c, double* dst, size_t n);
    // dst = -(a * b) - c
    void nfmsub_fp64(const double* a, const double* b, const double* c, double* dst, size_t n);
    // dst = -src
    void neg_fp64(const double* src, double* dst, size_t n);
    // dst = a^b
    void pow_fp64(double* src1, double* src2, double* dst, size_t n);
    void ipow_fp64(double src1, double* src2, double* dst, size_t n);
    void powi_fp64(double* src1, double src2, double* dst, size_t n);
    // dst = sqrt(src)
    void sqrt_fp64(const double* src, double* dst, size_t n);
    // dst = abs(src)
    void abs_fp64(const double* src, double* dst, size_t n);

    // dst (bool:i64) = src1 == src2
    void eq_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void eqi_fp64(const double* src1, double src2, int64_t* dst, size_t n);
    // dst (bool:i64) = src1 != src2
    void neq_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void neqi_fp64(const double* src1, double src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 < src2
    void lt_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void lti_fp64(const double* src1, double src2, int64_t* dst, size_t n);
    void ilt_fp64(double src1, const double* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 <= src2
    void lte_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void ltei_fp64(const double* src1, double src2, int64_t* dst, size_t n);
    void ilte_fp64(double src1, const double* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 > src2
    void gt_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void gti_fp64(const double* src1, double src2, int64_t* dst, size_t n);
    void igt_fp64(double src1, const double* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 >= src2
    void gte_fp64(const double* src1, const double* src2, int64_t* dst, size_t n);
    void gtei_fp64(const double* src1, double src2, int64_t* dst, size_t n);
    void igte_fp64(double src1, const double* src2, int64_t* dst, size_t n);

    // dst (f64) = sign(src)
    void sign_fp64(const double* src, double* dst, size_t n);
    // dst = ln(src)
    void log_fp64(const double* src, double* dst, size_t n);
    // dst = log2(src)
    void log2_fp64(const double* src, double* dst, size_t n);
    // dst = log10(src)
    void log10_fp64(const double* src, double* dst, size_t n);
    // dst = e^src
    void exp_fp64(const double* src, double* dst, size_t n);
    // dst = floor(src)
    void floor_fp64(const double* src, double* dst, size_t n);
    // dst = ceil(src)
    void ceil_fp64(const double* src, double* dst, size_t n);
    // dst = round(src)
    void round_fp64(const double* src, double* dst, size_t n);
    // dst = sin(src)
    void sin_fp64(const double* src, double* dst, size_t n);
    // dst = cos(src)
    void cos_fp64(const double* src, double* dst, size_t n);
    // dst = tan(src)
    void tan_fp64(const double* src, double* dst, size_t n);
    // dst = erf(src)
    void erf_fp64(double* src, double* dst, size_t n);
    // dst = cdfnorm(src)
    void cdfnorm_fp64(const double* src, double* dst, size_t n);

    void cast_f64_i64(const double* src, int64_t* dst, size_t n);
    void cast_i64_f64(const int64_t* src, double* dst, size_t n);

    void add_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void addi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    void sub_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void subi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void isub_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    void mul_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void muli_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    void div_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void divi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void idiv_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    void mod_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void modi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void imod_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    void neg_i64(const double* src, double* dst, size_t n);
    void abs_i64(const int64_t* src, int64_t* dst, size_t n);
    // dst (bool:i64) = src1 == src2
    void eq_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void eqi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 != src2
    void neq_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void neqi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 < src2
    void lt_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void lti_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void ilt_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 <= src2
    void lte_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void ltei_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void ilte_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 > src2
    void gt_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void gti_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void igt_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    // dst (bool:i64) = src1 >= src2
    void gte_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void gtei_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);
    void igte_i64(int64_t src1, const int64_t* src2, int64_t* dst, size_t n);

    // Used with boolean representations of i64
    void not_i64(const int64_t* src, int64_t* dst, size_t n);

    void and_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void andi_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    void or_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void ori_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);

    void xor_i64(const int64_t* src1, const int64_t* src2, int64_t* dst, size_t n);
    void xori_i64(const int64_t* src1, int64_t src2, int64_t* dst, size_t n);


    int64_t get_days_since_epoch(const int64_t* ts);
    int64_t get_seconds_of_day(const int64_t* ts);

    int64_t get_year(const int64_t* ts);
    int64_t get_month(const int64_t* ts);
    int64_t get_day(const int64_t* ts);
    int64_t get_hour(const int64_t* ts);
    int64_t get_minute(const int64_t* ts);
    int64_t get_second(const int64_t* ts);
    int64_t get_day_of_year(const int64_t* ts);
    int64_t get_week_of_year(const int64_t* ts);
    int64_t get_day_of_week(const int64_t* ts);

}