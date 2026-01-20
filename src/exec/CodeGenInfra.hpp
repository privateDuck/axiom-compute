#pragma once

#include <cstdint>
#include "Instruction.hpp"
#include "OpCodes.hpp"
#include "absl/container/flat_hash_set.h"
#include "absl/container/flat_hash_map.h"

class StateManager {
private:
	absl::flat_hash_set<int16_t> free_registers;
	constexpr static int16_t MAX_REGISTERS = 256;
public:
	StateManager() {
		free_registers.reserve(MAX_REGISTERS);
		for (int16_t i = 0; i < MAX_REGISTERS; ++i) {
			free_registers.insert(i);
		}
	}
	int16_t AllocateRegister() {
		if (free_registers.empty()) {
			// In a real implementation, we would handle register spilling here.
			throw std::runtime_error("No free registers available");
		}
		auto it = free_registers.begin();
		int16_t reg = *it;
		free_registers.erase(it);
		return reg;
	}
	void FreeRegister(int16_t reg) {
		free_registers.insert(reg);
	}
	size_t TotalAllocatedRegisters() const {
		return MAX_REGISTERS - free_registers.size();
	}
};