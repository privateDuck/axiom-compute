#pragma once

#include <cstdint>

struct alignas(16) Instruction {
	uint16_t op_code;
	int16_t dest_idx;
	int16_t opr1_idx;
	int16_t opr2_idx;

	union {
		double as_double;
		int64_t as_int;
	} imm;
};