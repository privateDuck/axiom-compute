// atlas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <format>
#include <iostream>
#include "../exec/ExecutionEngine.hpp"
#include "src/data/DataIngester.hpp"

struct AddNode {
	std::vector<int> compute(const std::vector<int>& inputs, std::vector<int>& outputs, size_t num_outs, int) {
		int sum = 0;
		for (const auto& val : inputs) sum += val;
		outputs[0] = sum;
	}
};

struct MultNode {
	std::vector<int> compute(const std::vector<int>& inputs, std::vector<int>& outputs, size_t num_outs, int) {
		int product = 1;
		for (const auto& val : inputs) product *= val;
		outputs[0] = product;
	}
};

struct InputNode {
	int value;
	void setValue(int v) { value = v; };

	std::vector<int> compute(const std::vector<int>& inputs, std::vector<int>& outputs, size_t num_outs, int) {
		outputs[0] = inputs[0];
	}
};



int main() {
	std::cout << "Helloc" << std::endl;
}