// flat_map_demo.cpp
// Demonstrates the FlatMap interface.  Compile with:
//   g++ -std=c++20 -Wall -Wextra -o demo flat_map_demo.cpp
//
// (flat_map.hpp must be in the same directory)
#include "FlatMap.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>

// ── helpers ──────────────────────────────────────────────────────────────────

static void print_value(const FlatMap::Value& v) {
    std::visit([](const auto& x) {
        using T = std::decay_t<decltype(x)>;
        if      constexpr (std::is_same_v<T, int64_t>)     std::cout << "(i64) " << x;
        else if constexpr (std::is_same_v<T, double>)      std::cout << "(f64) " << x;
        else if constexpr (std::is_same_v<T, std::string>) std::cout << "(str) \"" << x << '"';
    }, v);
}

static const char* type_name(FlatMap::ValueType t) {
    switch (t) {
    case FlatMap::ValueType::Int64:   return "Int64";
    case FlatMap::ValueType::Float64: return "Float64";
    case FlatMap::ValueType::String:  return "String";
    case FlatMap::ValueType::Bool:    return "Bool";
    case FlatMap::ValueType::Timestamp:return "Timestamp";
    }
    return "?";
}

// ── main ─────────────────────────────────────────────────────────────────────

int main() {
    FlatMap m;

    // ── Insert values of different types ────────────────────────────────────
    m.insert(10,  int64_t{42});
    m.insert(5,   3.14159);
    m.insert(20,  std::string_view{"hello"});
    m.insert(-3,  int64_t{-999});
    m.insert(15,  std::string_view{"world"});

    std::cout << "=== After 5 inserts ===\n";
    std::cout << "size        : " << m.size()      << '\n';
    std::cout << "byte_size   : " << m.byte_size() << " bytes\n\n";

    // ── contains ────────────────────────────────────────────────────────────
    for (int64_t k : {-3, 5, 10, 15, 20, 99}) {
        std::cout << "contains(" << k << ") = " << std::boolalpha << m.contains(k) << '\n';
    }

    // ── type_of ─────────────────────────────────────────────────────────────
    std::cout << "\n=== type_of ===\n";
    for (int64_t k : {-3, 5, 10, 15, 20}) {
        auto t = m.type_of(k);
        assert(t.has_value());
        std::cout << "key " << k << " -> " << type_name(*t) << '\n';
    }

    // ── get ─────────────────────────────────────────────────────────────────
    std::cout << "\n=== get ===\n";
    for (int64_t k : {-3, 5, 10, 15, 20}) {
        auto v = m.get(k);
        assert(v.has_value());
        std::cout << "key " << k << " -> ";
        print_value(*v);
        std::cout << '\n';
    }
    assert(!m.get(99).has_value()); // missing key

    // ── Overwrite existing keys ──────────────────────────────────────────────
    std::cout << "\n=== Overwrite key 20 (string→i64) and key 5 (f64→longer string) ===\n";
    m.insert(20, int64_t{777});
    m.insert(5,  std::string_view{"a much longer string than before"});
    m.insert(80, true);

    std::cout << "Value at 80 " << m.get_bool(80) << '\n';
    std::cout << "Value at 5 " << m.get_string(5) << '\n';

    std::cout << "key 20 -> "; print_value(*m.get(20)); std::cout << '\n';
    std::cout << "key  5 -> "; print_value(*m.get(5));  std::cout << '\n';
    std::cout << "byte_size after overwrite: " << m.byte_size() << " bytes\n";

    return 0;
}