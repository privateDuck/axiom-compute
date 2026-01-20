#pragma once


enum class OPCODE {
	NOP = 0, // End
	// Arithmetic
	ADD = 1,
	ADD_IMM = 2,
	SUB = 3,
	SUB_IMM = 4,
	MUL = 5,
	MUL_IMM = 6,
	DIV = 7,
	DIV_IMM = 8,
	POW = 9,
	POW_IMM = 10,
	// Comparison
	EQ = 20,
	NEQ = 21,
	LT = 22,
	LTE = 23,
	GT = 24,
	GTE = 25,
	// Logical
	AND = 30,
	OR = 31,
	NOT = 32,
	// Vector Functions
	NEGATE = 39,
	SQRT = 40,
	ABS = 41,
	LN = 42,
	LOG10 = 43,
	LOG2 = 44,
	EXP = 45,
	SIN = 46,
	COS = 47,
	TAN = 48,
	ARCSIN = 49,
	ARCCOS = 50,
	ARCTAN = 51,
	SINH = 52,
	COSH = 53,
	TANH = 54,
	FLOOR = 55,
	CEIL = 56,
	ROUND = 57,
	// Aggregate Functions
	SUM = 70,
	MEAN = 71,
	MIN = 72,
	MAX = 73,
	MIN_MAX = 74, // Only used internally
	COUNT = 75,
	COUNT_NON_NULL = 76,
	COUNT_DISTINCT = 77,
	STDDEV = 78, // operand 2 -> ddof
	VARIANCE = 79, // operand 2 -> ddof
	SKEW = 80,
	KURTOSIS = 81,
	MODE = 82,
	PRODUCT = 83,
	// Internal Operations
	LOAD_COLUMN = 90,
	SAVE_COLUMN = 91,
	LOAD_CONSTANT = 92,
	STORE_SCALAR = 93, // Store scalar value from operand 1 into state_buffer at index operand 1
	CHECKPOINT = 94,
	TRAIN_ONLY = 95, // Markers for training only code sections
};