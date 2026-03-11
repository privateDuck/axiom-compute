#include "functions.hpp"
#include <Eigen/Geometry>
//#include "../stats/Descriptive.hpp"
#include "TimeConvertions.hpp"
#include <unordered_map>
#include <unordered_set>

double compute_fv(double rate, double nper, double pmt, double pv) {
    if (rate == 0.0) return -(pv + pmt * nper);
    double term = std::pow(1.0 + rate, nper);
    return -(pv * term + pmt * (term - 1.0) / rate);
}

double compute_pv(const double rate, const double nper, const double pmt, const double fv) {
    if (rate == 0.0) return -(fv + pmt * nper);
    const double term = std::pow(1.0 + rate, nper);
    return -(fv + pmt * (term - 1.0) / rate) / term;
}

double compute_pmt(const double rate, const double nper, const double pv, const double fv) {
    if (rate == 0.0) return -(fv + pv) / nper;
    const double term = std::pow(1.0 + rate, nper);
    return -(fv + pv * term) * rate / (term - 1.0);
}

double compute_nper(const double rate, const double pmt, const double pv, const double fv) {
    if (rate == 0.0) return -(fv + pv) / pmt;
    // Solve: pv*(1+rate)^nper + pmt*((1+rate)^nper - 1)/rate + fv = 0
    const double num = pmt - fv * rate;
    const double den = pmt + pv * rate;
    if (den == 0.0) throw std::domain_error("nper divide by zero");
    return std::log(num / den) / std::log(1.0 + rate);
}

double calculate_npv(const Eigen::Ref<const EigenColDoubleVec>& cashFlows, const double rate) {
    double npv = 0.0;
    for (int t = 0; t < cashFlows.size(); ++t) {
        npv += cashFlows(t) / std::pow(1 + rate, t);
    }
    return npv;
}

double calculate_npv_derivative(const Eigen::Ref<const EigenColDoubleVec>& cashFlows, const double rate) {
    double derivative = 0.0;
    for (int t = 1; t < cashFlows.size(); ++t) {
        derivative -= t * cashFlows(t) / std::pow(1 + rate, t + 1);
    }
    return derivative;
}

// Internal Rate of Return (IRR)
double calculate_irr(const Eigen::Ref<const EigenColDoubleVec>& cashFlows, const double initialGuess = 0.1) {
    double rate = initialGuess;
    double npv = 0.0;
    double derivative = 0.0;
    constexpr int maxIterations = 100;
    constexpr double tolerance = 0.00001;

    for (int i = 0; i < maxIterations; ++i) {
        npv = calculate_npv(cashFlows, rate);
        derivative = calculate_npv_derivative(cashFlows, rate);

        if (std::abs(npv) < tolerance) {
            return rate; // IRR found
        }

        if (std::abs(derivative) < 1e-6) {
            // Avoid division by zero if derivative is too close to zero
            break;
        }

        rate = rate - npv / derivative; // Newton-Raphson formula
    }

    return rate;
}

double single_sort_count_distinct(const Eigen::Ref<const EigenColDoubleVec>& ref) {
    std::vector<uint64_t> int_vec(ref.size());
    std::memcpy(int_vec.data(), ref.data(), int_vec.size() * sizeof(uint64_t));
    std::ranges::sort(int_vec);
    uint64_t counter = 0;
    for (size_t i = 1; i < int_vec.size(); ++i) {
        if (int_vec[i - 1] != int_vec[i]) counter++;
    }
    return static_cast<double>(counter);
}

size_t count_distinct_exact(const Eigen::VectorXd& vec) {
    // We use uint64_t to represent the raw bits of the double
    std::unordered_set<uint64_t> distinct_elements;
    distinct_elements.reserve(vec.size());

    for (int i = 0; i < vec.size(); ++i) {
        uint64_t bits;
        std::memcpy(&bits, &vec(i), sizeof(double));
        distinct_elements.insert(bits);
    }
    return distinct_elements.size();
}

double find_mode_exact(const Eigen::VectorXd& vec) {
    if (vec.size() == 0) return 0.0;

    std::unordered_map<uint64_t, int> counts;
    uint64_t best_bits = 0;
    int max_count = 0;

    for (int i = 0; i < vec.size(); ++i) {
        uint64_t bits;
        std::memcpy(&bits, &vec(i), sizeof(double));

        int new_count = ++counts[bits];
        if (new_count > max_count) {
            max_count = new_count;
            best_bits = bits;
        }
    }

    double mode_val;
    std::memcpy(&mode_val, &best_bits, sizeof(double));
    return mode_val;
}

scripting::fluxpp::FN_ORDER scripting::fluxpp::get_fn_order(const uint64_t index) {
    if (index < 39 || index > 80) return FN_ORDER::SCALAR_SCALAR;
    if (index < 43) return FN_ORDER::VECTOR_SCALAR;
    if (index < 59) return FN_ORDER::SCALAR_VECTOR;
    if (index < 63) return FN_ORDER::VECTOR_VECTOR;
    return FN_ORDER::SCALAR_SCALAR;
}

bool scripting::fluxpp::is_aggregated(const uint64_t index) {
    return index > 100 && index < 200;
}

scripting::fluxpp::FN_DATA scripting::fluxpp::get_fn_index(const std::string &fn) {
    if (fn_index_map.contains(fn)) {
        return fn_index_map[fn];
    }
    else {
        return {std::numeric_limits<uint64_t>::max(), Type::TNULL, false, false};
    }
}

double scripting::fluxpp::resolve_scalar_function_scalar(const ArgArray &args, const uint64_t index) {
    switch (index) {
        case 0:  return std::abs(args[0]);
        case 1:  return (args[0] > 0.0) - (args[0] < 0.0); // sign function
        case 2:  return std::sin(args[0]);
        case 3:  return std::cos(args[0]);
        case 4:  return std::tan(args[0]);
        case 5:  return std::asin(args[0]);
        case 6:  return std::acos(args[0]);
        case 7:  return std::atan(args[0]);
        case 8:  return std::sinh(args[0]);
        case 9:  return std::cosh(args[0]);
        case 10: return std::tanh(args[0]);
        case 11: return std::asinh(args[0]);
        case 12: return std::acosh(args[0]);
        case 13: return std::atanh(args[0]);
        case 14: return std::exp(args[0]);
        case 15: return std::exp2(args[0]);
        case 16: return std::expm1(args[0]);
        case 17: return std::log(args[0]); // Handles both "log" and "ln"
        case 18: return std::log10(args[0]);
        case 19: return std::log2(args[0]);
        case 20: return std::sqrt(args[0]);
        case 21: return std::cbrt(args[0]);
        case 22: return std::floor(args[0]);
        case 23: return std::ceil(args[0]);
        case 24: return std::trunc(args[0]);
        case 25: return std::round(args[0]);
        case 26: return std::rint(args[0]);
        case 27: return std::erf(args[0]);
        case 28: return std::erfc(args[0]);
        case 29: return std::tgamma(args[0]);
        case 30: return std::lgamma(args[0]);

        // --- 2 Argument Functions ---

        case 31: return std::pow(args[0], args[1]);
        case 32: return std::atan2(args[0], args[1]);
        case 33: return std::hypot(args[0], args[1]);
        case 34: return std::fmod(args[0], args[1]);

        // --- 4 Argument Functions (Financials) ---
        // Note: Standard financial formulas assuming end-of-period payments.
        // args = [rate, nper, pmt, pv] or variants thereof depending on the function.

        case 35: {
            // fv(rate, nper, pmt, pv)
            const double rate = args[0], nper = args[1], pmt = args[2], pv = args[3];
            return compute_fv(rate, nper, pmt, pv);
        }
        case 36: {
            // pv(rate, nper, pmt, fv)
            const double rate = args[0], nper = args[1], pmt = args[2], fv = args[3];
            return compute_pv(rate, nper, pmt, fv);
        }
        case 37: {
            // pmt(rate, nper, pv, fv)
            const double rate = args[0], nper = args[1], pv = args[2], fv = args[3];
            return compute_pmt(rate, nper, pv, fv);
        }
        case 38: {
            // nper(rate, pmt, pv, fv)
            const double rate = args[0], pmt = args[1], pv = args[2], fv = args[3];
            return compute_nper(rate, pmt, pv, fv);
        }

        // Date calculations
        case 84: {
            // get year
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_year(ts);
        }
        case 85: {
            // get day of year
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_day_of_year(ts);
        }
        case 86: {
            // get month
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_month(ts);
        }
        case 87: {
            // get day
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_day(ts);
        }
        case 88: {
            // get day of week
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_day_of_week(ts);
        }
        case 89: {
            // get week_of_year
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_week_of_year(ts);
        }
        case 90: {
            // get hour
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_hour(ts);
        }
        case 91: {
            // get minute
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_minute(ts);
        }
        case 92: {
            // get second
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_second(ts);
        }
        case 93: {
            // get second of day
            const auto ts = std::bit_cast<uint64_t>(args[0]);
            return get_seconds_of_day(ts);
        }
        default:
            throw std::invalid_argument("Unknown scalar function index.");
    }
}

double scripting::fluxpp::resolve_scalar_function_vector(const VectorArgArray &args, const uint64_t index,
    const uint32_t ndims) {
    switch (index) {
        case 43: // sum
            return args[0].array().sum();
        case 44: // mean
            return args[0].array().mean();
        case 45: // min
            return args[0].array().minCoeff();
        case 46: // max
            return args[0].array().maxCoeff();
        case 47: // count
            return static_cast<double>(args[0].size());
        case 48: // count_distinct
            return single_sort_count_distinct(args[0]);
        case 49: // stddev
        {
            const double var = (args[0].array() - args[0].array().mean()).square().mean();
            return std::sqrt(var);
        }
        case 50: // variance
            return (args[0].array() - args[0].array().mean()).square().mean();
        case 51: // skew
            return 0;// stats::skewness(args[0].data(), ndims);
        case 52: // kurtosis
            return 0; // stats::kurtosis(args[0].data(), ndims);
        case 53: // mode
            uint64_t max;
        case 54: // product
            return args[0].prod();
        case 55: // norm
            return args[0].norm();
        case 56: // irr
            return calculate_irr(args[0]);

            // --- 2-Vector / Mixed Arguments ---
        case 57: // dot
            return args[0].dot(args[1]);
        case 58: // npv
            return calculate_npv(args[0], args[1](0));
        default:
            throw std::invalid_argument("Unknown scalar function index.");
    }
}

EigenColDoubleVec scripting::fluxpp::resolve_vector_function_scalar(const ArgArray &args, const uint32_t index, const uint32_t ndims) {
    EigenColDoubleVec vec(ndims);
    std::mt19937_64 rng = GlobalRandomEngine::getInstance().getRandomEngine();

    switch (index) {
        case 39:
        {
            std::exponential_distribution<> expd(args[0]);
            for (uint32_t i = 0; i < ndims; i++) {
                vec(i) = expd(rng);
            }
            break;
        }
        case 40:
        {
            std::normal_distribution<> normd(args[0], args[1]);
            for (uint32_t i = 0; i < ndims; i++) {
                vec(i) = normd(rng);
            }
            break;
        }
        case 41:
        {
            std::uniform_real_distribution<> und(args[0], args[1]);
            for (uint32_t i = 0; i < ndims; i++) {
                vec(i) = und(rng);
            }
            break;
        }
        case 42:
        {
            vec.setLinSpaced(ndims, args[0], args[1]);
            break;
        }
        default:
            throw std::invalid_argument("Unknown scalar function index.");
    }

    return vec;
}

EigenColDoubleVec scripting::fluxpp::resolve_vector_function_vector(const VectorArgArray &args, const uint32_t index,
    const uint32_t ndims) {
    switch (index) {
        case 0:  // abs
            return args[0].cwiseAbs();
        case 1:  // sign
            return args[0].cwiseSign();
        case 2:  // sin
            return args[0].array().sin();
        case 3:  // cos
            return args[0].array().cos();
        case 4:  // tan
            return args[0].array().tan();
        case 5:  // asin
            return args[0].array().asin();
        case 6:  // acos
            return args[0].array().acos();
        case 7:  // atan
            return args[0].array().atan();
        case 8:  // sinh
            return args[0].array().sinh();
        case 9:  // cosh
            return args[0].array().cosh();
        case 10: // tanh
            return args[0].array().tanh();
        case 11: // asinh
            return args[0].array().asinh();
        case 12: // acosh
            return args[0].array().acosh();
        case 13: // atanh
            return args[0].array().atanh();
        case 14: // exp
            return args[0].array().exp();
        case 15: // exp2
            return args[0].array().exp2();
        case 16: // expm1
            return args[0].array().expm1();
        case 17: // log / ln
            return args[0].array().log();
        case 18: // log10
            return args[0].array().log10();
        case 19: // log2
            return args[0].array().log2();
        case 20: // sqrt
            return args[0].array().sqrt();
        case 21: // cbrt
            return args[0].array().cbrt();
        case 22: // floor
            return args[0].array().floor();
        case 23: // ceil
            return args[0].array().ceil();
        case 24: // trunc
            return args[0].array().trunc();
        case 25: // round
            return args[0].array().round();
        case 26: // rint
            return args[0].array().rint();
        case 27: // erf
            return args[0].array().unaryExpr([](const double d) -> double {return std::erf(d); });
        case 28: // erfc
            return args[0].array().unaryExpr([](const double d) -> double {return std::erfc(d); });
        case 29: // tgamma
            return args[0].array().unaryExpr([](const double d) -> double {return std::tgamma(d); });
        case 30: // lgamma
            return args[0].array().unaryExpr([](const double d) -> double {return std::lgamma(d); });
        // --- 2-Argument ---
        case 31: // pow
            return args[0].array().pow(args[1].array());
        case 32: // atan2
            return args[0].array().atan2(args[1].array());

        // --- 4-Argument ---
        case 35: // fv
        {
            EigenColDoubleVec vec(ndims);
            for (int i = 0; i < ndims; ++i) {
                vec(i) = compute_fv(args[0](i),args[1](i),args[2](i),args[3](i));
            }
            return vec;
        }
        case 36: // pv
        {
            EigenColDoubleVec vec(ndims);
            for (int i = 0; i < ndims; ++i) {
                vec(i) = compute_pv(args[0](i),args[1](i),args[2](i),args[3](i));
            }
            return vec;
        }
        case 37: // pmt
        {
            EigenColDoubleVec vec(ndims);
            for (int i = 0; i < ndims; ++i) {
                vec(i) = compute_pmt(args[0](i),args[1](i),args[2](i),args[3](i));
            }
            return vec;
        }
        case 38: // nper
        {
            EigenColDoubleVec vec(ndims);
            for (int i = 0; i < ndims; ++i) {
                vec(i) = compute_nper(args[0](i),args[1](i),args[2](i),args[3](i));
            }
            return vec;
        }

        // Vector Vector Operations
        case 59: // cumsum
        {
            EigenColDoubleVec cum_sum_vector(ndims);
            double sum = 1.0;
            for (int i = 0; i < ndims; ++i) {
                sum *= args[0](i);
                cum_sum_vector(i) = sum;
            }
            return cum_sum_vector;
        }
        case 60: // cumprod
        {
            EigenColDoubleVec cum_product_vector(ndims);
            double product = 1.0;
            for (int i = 0; i < ndims; ++i) {
                product *= args[0](i);
                cum_product_vector(i) = product;
            }
            return cum_product_vector;
        }
        case 61: // diff
        {
            return args[0].tail(ndims-1) - args[0].head(ndims-1);
        }
        case 62: // normalize
            return args[0].normalized();


        case 84: {
            // get year
            return args[0].unaryExpr([](const double d)->double{ return get_year(std::bit_cast<uint64_t>(d)); });
        }
        case 85: {
            // get day of year
            return args[0].unaryExpr([](const double d)->double{ return get_day_of_year(std::bit_cast<uint64_t>(d)); });
        }
        case 86: {
            // get month
            return args[0].unaryExpr([](const double d)->double{ return get_month(std::bit_cast<uint64_t>(d)); });
        }
        case 87: {
            // get day
            return args[0].unaryExpr([](const double d)->double{ return get_day(std::bit_cast<uint64_t>(d)); });
        }
        case 88: {
            // get day of week
            return args[0].unaryExpr([](const double d)->double{ return get_day_of_week(std::bit_cast<uint64_t>(d)); });
        }
        case 89: {
            // get week_of_year
            return args[0].unaryExpr([](const double d)->double{ return get_week_of_year(std::bit_cast<uint64_t>(d)); });
        }
        case 90: {
            // get hour
            return args[0].unaryExpr([](const double d)->double{ return get_hour(std::bit_cast<uint64_t>(d)); });
        }
        case 91: {
            // get minute
            return args[0].unaryExpr([](const double d)->double{ return get_minute(std::bit_cast<uint64_t>(d)); });
        }
        case 92: {
            // get second
            return args[0].unaryExpr([](const double d)->double{ return get_second(std::bit_cast<uint64_t>(d)); });
        }
        case 93: {
            // get second of day
            return args[0].unaryExpr([](const double d)->double{ return get_seconds_of_day(std::bit_cast<uint64_t>(d)); });
        }
        default:
            throw std::runtime_error("Invalid argument");
    }

}
