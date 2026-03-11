#pragma once

#include "types.hpp"
#include "TimeConvertions.hpp"
#include <variant>
#include <bit>
#include "EigenDefinitions.hpp"

namespace scripting::fluxpp {
    using ValueType = std::variant<EigenColDoubleVec, double>;
    template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

    struct ExprReturn {
        Type type;
        bool isConst;
        bool isVector;
        bool isNull;
        ValueType value;

        static ExprReturn MakeConstBool(const bool value) {
            ExprReturn ret;
            ret.isConst = true;
            ret.value = value ? 1.0 : 0.0;
            ret.type = Type::TBOOL;
            ret.isVector = false;
            ret.isNull = false;
            return ret;
        }

        static ExprReturn MakeConstReal(const double value) {
            ExprReturn ret;
            ret.isConst = true;
            ret.value = value;
            ret.type = Type::TREAL;
            ret.isVector = false;
            ret.isNull = false;
            return ret;
        }

        static ExprReturn MakeConstDateTime(const std::string& value) {
            ExprReturn ret;
            const uint64_t ts = parse_datetime(value);
            const double tsdbits = std::bit_cast<double>(ts);
            ret.isConst = true;
            ret.value = tsdbits;
            ret.type = Type::TTIMESTAMP;
            ret.isVector = false;
            ret.isNull = false;
            return ret;
        }

        static ExprReturn MakeConstDate(const std::string& value) {
            ExprReturn ret;
            const uint64_t ts = parse_date(value);
            const auto tsdbits = std::bit_cast<double>(ts);
            ret.isConst = true;
            ret.value = tsdbits;
            ret.type = Type::TTIMESTAMP;
            ret.isVector = false;
            ret.isNull = false;
            return ret;
        }

        static ExprReturn MakeConstTime(const std::string& value) {
            ExprReturn ret;
            const uint64_t ts = parse_time(value);
            const double tsdbits = std::bit_cast<double>(ts);
            ret.isConst = true;
            ret.value = tsdbits;
            ret.type = Type::TTIMESTAMP;
            ret.isVector = false;
            ret.isNull = false;
            return ret;
        }

        static ExprReturn OperatorAbsConst(const ExprReturn& val) {
            ExprReturn ret;
            ret.isConst = true;
            ret.type = val.type;
            std::visit(Overloaded {
                [&](const double d) { ret.value = fabs(d); },
                [&](const Eigen::Ref<const EigenColDoubleVec>& vec) {ret.value = vec.norm();},
            }, val.value);
            return ret;
        }

        static ExprReturn OperatorFunctionConst(const ExprReturn& val) {
            ExprReturn ret;
            ret.isConst = true;
            ret.type = val.type;
            std::visit(Overloaded {
                [&](const double d) { ret.value = fabs(d); },
                [&](const Eigen::Ref<const EigenColDoubleVec>& vec) {ret.value = vec.norm();},
            }, val.value);
            return ret;
        }
    };
}
