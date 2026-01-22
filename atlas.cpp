// atlas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <format>
#include <iostream>
#include "../exec/ExecutionEngine.hpp"
#include "src/data/DataIngester.hpp"

using NType = double;

struct AddNode {
	std::vector<NType> compute(const std::vector<NType>& inputs, std::vector<NType>& outputs, size_t num_outs, int) {
		NType sum = 0;
		for (const auto& val : inputs) sum += val;
		outputs[0] = sum;
	}

	void init(NodeId i) {

	}
};

struct MultNode {
	std::vector<NType> compute(const std::vector<NType>& inputs, std::vector<NType>& outputs, size_t num_outs, int) {
		NType product = 1;
		for (const auto& val : inputs) product *= val;
		outputs[0] = product;
	}
	void init(NodeId i) {

	}
};

struct InputNode {
	NType value;
	void setValue(NType v) { value = v; };

	std::vector<NType> compute(const std::vector<NType>& inputs, std::vector<NType>& outputs, size_t num_outs, int) {
		outputs[0] = inputs[0];
	}
	void init(NodeId i) {

	}
};

using NodeVar = std::variant<AddNode, MultNode, InputNode>;

int main() {
	DAGEngine<NodeVar, double, int> graph;
	auto inA = graph.addNode(InputNode{10.0});
	auto inB = graph.addNode(InputNode{10.0});
	auto add = graph.addNode(AddNode{});
	auto mul = graph.addNode(MultNode{});

	graph.addEdge(inA, 0, add, 0);
	graph.addEdge(inB, 0, add, 1);
	graph.addEdge(add, 0, mul, 0);
	graph.addEdge(inB, 0, mul, 1);

	graph.compile();
	graph.execute(1);
	auto result = graph.getOutput(mul, 0);
	std::cout << result << std::endl;
}