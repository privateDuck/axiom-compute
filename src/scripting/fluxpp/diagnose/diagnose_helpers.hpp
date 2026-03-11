#pragma once
// ============================================================
//  FluxPP — DiagnosticHelpers.h
//
//  Inline utilities for building consistent, human-readable
//  diagnostic message fragments inside visitor methods.
//
//  These helpers produce the strings that go into the
//  .what() / .expected() / .found() / .fix() slots.
//  Using them keeps wording consistent across the codebase.
// ============================================================

#include <string>
#include <string_view>
#include <cstdint>
#include "../types.hpp"

namespace scripting::fluxpp {

// ── Type / Dimensionality vocabulary ─────────────────────────────────────────
// Adjust these enums to match your actual IR type system.

/*enum class Type : uint8_t {
    Real,
    Bool,
    Timestamp,
    String,
    Unknown,
};*/

enum class Dim : uint8_t {
    Scalar,
    Vector,
    Unknown,
};

// ── Primitive formatters ──────────────────────────────────────────────────────

inline std::string_view typeName(Type t) noexcept {
    switch (t) {
        case Type::TREAL:      return "real";
        case Type::TBOOL:      return "bool";
        case Type::TTIMESTAMP: return "timestamp";
        case Type::TSTRING:    return "string";
        case Type::TNULL:   return "<unknown>";
    }
    return "<unknown>";
}

inline bool supportsComparisons(const Type t) noexcept {
    return t == Type::TREAL || t == Type::TTIMESTAMP;
}

inline std::string_view dimName(Dim d) noexcept {
    switch (d) {
        case Dim::Scalar:  return "scalar";
        case Dim::Vector:  return "vector";
        case Dim::Unknown: return "<unknown>";
    }
    return "<unknown>";
}

inline std::string_view dimName(bool isVector) noexcept {
    return isVector ? "vector" : "scalar";
}

// "real scalar", "bool vector", …
inline std::string fmtTypeDim(Type t, Dim d) {
    return std::string(typeName(t)) + ' ' + std::string(dimName(d));
}

// "real" (no dim) — for type-only messages
inline std::string fmtType(Type t) {
    return std::string(typeName(t));
}

// "'foo' (real scalar)"
inline std::string fmtIdTypeDim(std::string_view id, Type t, Dim d) {
    return "'" + std::string(id) + "' (" + fmtTypeDim(t, d) + ")";
}

// ── Common "what" builders ────────────────────────────────────────────────────

inline std::string whatReassign(std::string_view varName) {
    return "Reassignment to immutable variable '" + std::string(varName) + "'";
}

inline std::string whatUnknownCol(std::string_view colName) {
    return "Reference to undeclared column '" + std::string(colName) + "'";
}

inline std::string whatUnknownId(std::string_view id) {
    return "Reference to undeclared identifier '" + std::string(id) + "'";
}

inline std::string whatUnknownFn(std::string_view fnName) {
    return "Call to undeclared function '" + std::string(fnName) + "'";
}

inline std::string whatTypeMismatch(std::string_view context,
                                     Type lhsType, Dim lhsDim,
                                     Type rhsType, Dim rhsDim) {
    return std::string(context) + " type mismatch: '"
        + fmtTypeDim(lhsType, lhsDim) + "' vs '"
        + fmtTypeDim(rhsType, rhsDim) + "'";
}

inline std::string whatWrongArgCount(std::string_view fnName,
                                      uint32_t expected,
                                      uint32_t found) {
    return "'" + std::string(fnName) + "' expects "
        + std::to_string(expected) + " argument(s), "
        + std::to_string(found) + " given";
}

// ── Common "expected" builders ────────────────────────────────────────────────

inline std::string expType(Type t) {
    return "expression of type " + fmtType(t);
}

inline std::string expTypeDim(Type t, Dim d) {
    return fmtTypeDim(t, d) + " expression";
}

inline std::string expDim(Dim d) {
    return std::string(dimName(d)) + " expression";
}

inline std::string expBoolScalar() {
    return "bool scalar expression (condition)";
}

inline std::string expBoolVector() {
    return "bool vector expression (row mask)";
}

inline std::string expSameTypeAs(std::string_view colName, Type t) {
    return "expression matching column '" + std::string(colName)
        + "' type (" + fmtType(t) + ")";
}

// ── Common "found" builders ───────────────────────────────────────────────────

inline std::string foundTypeDim(Type t, Dim d) {
    return fmtTypeDim(t, d) + " expression";
}

inline std::string foundId(std::string_view id, Type t, Dim d) {
    return "'" + std::string(id) + "' evaluates to " + fmtTypeDim(t, d);
}

inline std::string foundArgCount(uint32_t n) {
    return std::to_string(n) + " argument(s) at call site";
}

// ── Common "fix" builders ─────────────────────────────────────────────────────

inline std::string fixRenameVar(std::string_view badName) {
    return "Choose a different name instead of '" + std::string(badName) + "'";
}

inline std::string fixCastTo(Type target) {
    return "Wrap the expression in an explicit cast to "
        + fmtType(target)
        + ", e.g. CAST(expr AS " + std::string(typeName(target)) + ")";
}

inline std::string fixWrapReduce(std::string_view fnHint = "SUM / AVG / COUNT") {
    return "Apply a reduction function (" + std::string(fnHint)
        + ") to produce a scalar, or remove the scalar requirement";
}

inline std::string fixAddCondition(std::string_view stmt) {
    return "Review the " + std::string(stmt)
        + " condition — every row is currently matched";
}

// ── Convenience: format a line reference ─────────────────────────────────────

inline std::string atLine(uint32_t line) {
    return "line " + std::to_string(line);
}

inline std::string firstDeclaredAt(std::string_view id, uint32_t line) {
    return "'" + std::string(id) + "' was first declared at " + atLine(line);
}

} // namespace fluxpp