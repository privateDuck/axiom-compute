#pragma once

#include <vector>
#include <variant>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdint>

using NodeId = uint32_t;
constexpr NodeId INVALID_ID = static_cast<NodeId>(-1);

// TNodeVariant: The variant of all node types
// TValue: The type of data flowing between wires (e.g., torch::Tensor or std::string table_name)
// TContext: External state needed for execution (e.g., duckdb::Connection& or DeviceConfig)
template <typename TNodeVariant, typename TValue, typename TContext>
class DAGEngine {
public:
    struct Connection { NodeId sourceNode; uint32_t sourcePort; };

    struct NodeEntry {
        TNodeVariant node;
        std::vector<Connection> inputs;
        std::vector<TValue> outputCache;
		size_t out_count = 0;
    };

    std::vector<NodeEntry> nodes;
    std::vector<NodeId> executionOrder;
    bool sorted = false;

    NodeId addNode(TNodeVariant&& node) {
        auto id = static_cast<NodeId>(nodes.size());
        nodes.push_back({ std::move(node), {}, {} });
        nodes.back().out_count = 0;
		// Initialize node if it has an init method
        std::visit([&](auto& n) { n.init(id); }, nodes.back().node);
        sorted = false;
        return id;
    }

    void addEdge(NodeId fromId, uint32_t fromPort, NodeId toId, uint32_t toPort) {
        if (toId < nodes.size()) {
            if (nodes[toId].inputs.size() <= toPort) nodes[toId].inputs.resize(toPort + 1, { INVALID_ID, 0 });
            nodes[toId].inputs[toPort] = { fromId, fromPort };
            sorted = false;
			nodes[fromId].out_count++; // Increment output count for fromId
        }
    }

    void compile() {
        executionOrder.clear();
        std::vector<uint8_t> visited(nodes.size(), 0); // 0=none, 1=visiting, 2=visited

        auto visit = [&](auto&& self, NodeId n) -> void {
            if (visited[n] == 2) return;
			if (visited[n] == 1) throw std::runtime_error("Cycle detected"); // Throwing acceptable since caller gurantees DAG
            visited[n] = 1;
            for (const auto& conn : nodes[n].inputs) {
                if (conn.sourceNode != INVALID_ID) self(self, conn.sourceNode);
            }
            visited[n] = 2;
            executionOrder.push_back(n);
            };

        for (NodeId i = 0; i < nodes.size(); ++i) {
            if (visited[i] == 0) visit(visit, i);
        }
        sorted = true;
    }

    // Execute logic that accepts a Context
    void execute(TContext context) {
        if (!sorted) compile();

        for (NodeId id : executionOrder) {
            auto& entry = nodes[id];

            std::vector<TValue> nodeInputs;
            nodeInputs.reserve(entry.inputs.size());

            for (const auto& conn : entry.inputs) {
                if (conn.sourceNode != INVALID_ID)
                    nodeInputs.push_back(nodes[conn.sourceNode].outputCache[conn.sourcePort]);
                else
                    nodeInputs.push_back(TValue{}); // disconnected ports
            }
            
            // Visitor passes both Inputs and Context
			// entry.outputCache.clear(); not needed since we reuse the vector
            entry.outputCache.reserve(entry.out_count);
            std::visit(
                [&](auto& n) { return n.compute(nodeInputs, entry.outputCache, entry.out_count, context); },
                entry.node
            );
        }
    }

    // Allow getting result of a specific node
    const TValue& getOutput(NodeId id, uint32_t port = 0) {
        return nodes[id].outputCache.at(port);
    }

    // Debug functions
	void printExecutionOrder() const {
		std::cout << "Execution Order: ";
		for (const NodeId id : executionOrder) {
			std::cout << id << " ";
		}
		std::cout << '\n';
	}
};