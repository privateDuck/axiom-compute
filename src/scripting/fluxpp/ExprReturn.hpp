#pragma once

#include "types.hpp"
#include "TimeConvertions.hpp"
#include <variant>
#include <bit>
#include "EigenDefinitions.hpp"

namespace scripting::fluxpp {

    using _Storage = std::vector<double, Eigen::aligned_allocator<double>>;
    using VectorXi64 = Eigen::Matrix<int64_t, Eigen::Dynamic, 1>;
    struct ConstEval {
        double data;
        uint16_t location;
        Type type;
        bool isVector;
        bool isNull;

        explicit ConstEval(const Type type_) : data(0.0), location(0), type(type_), isVector(false), isNull(false) {}

        void SetTimeStamp(const TimeStampAlignType ts) {
            data = std::bit_cast<double>(ts);
        }

        void SetReal(const double val) {
            data = val;
        }

        void SetBool(const bool val) {
            data = std::bit_cast<double>(val ? static_cast<int64_t>(1) : static_cast<int64_t>(0));
        }

        void SetStringIndex(const uint16_t index) {
            data = std::bit_cast<double>(static_cast<int64_t>(index));
        }

        void SetAsVector(const uint16_t loc) {
            location = loc;
            isVector = true;
        }

        [[nodiscard]] double asRealScalar() const {
            return data;
        }
        [[nodiscard]] TimeStampAlignType asTimeStampScalar() const {
            return std::bit_cast<TimeStampAlignType>(data);
        }
        [[nodiscard]] bool asBoolScalar() const {
            return std::bit_cast<int64_t>(data) != 0;
        }
        [[nodiscard]] int64_t asIntScalar() const {
            return std::bit_cast<int64_t>(data);
        }
    };

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
