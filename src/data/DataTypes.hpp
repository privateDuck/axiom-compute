//
// Created by Tharuka on 23/01/2026.
//

#ifndef ATLAS_DATATYPES_HPP
#define ATLAS_DATATYPES_HPP
#pragma once

// Weak types are inferred and only acts as a suggestion
// Weak types requires to be cast to their concrete types
// decided by the user
enum class InferredType {
    STRONG_NUMERICAL,
    WEAK_NUMERICAL,
    BOOLEAN,        // Inferred boolean, gets cast to int64
    STRONG_TIMESTAMP,
    WEAK_TIMESTAMP,
    STRONG_DATE,
    WEAK_DATE,
    STRONG_TIME,
    WEAK_TIME,
    STRING,
};

enum class ConcreteType {
    NUMERICAL,
    TIMESTAMP,
    DATE,
    TIME,
    ORDINAL,
    NOMINAL,    // Includes boolean
};

#endif //ATLAS_DATATYPES_HPP