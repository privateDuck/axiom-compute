//
// Created by Tharuka on 20/01/2026.
//

#pragma once

#include <vector>
#include <variant>
#include <algorithm>
#include <iostream>
#include <type_traits>

// --- Traits ---
template <typename T> struct is_read_only : std::false_type {};

template <typename TNodeVariant, typename TValue>
class ForwardExecutionEngine {
public:
    using NodeId = uint32_t;
    struct Connection { NodeId sourceNode; uint32_t sourcePort; };

    struct NodeEntry {
        TNodeVariant node;
        std::vector<Connection> inputs;
        std::vector<TValue> outputCache; // The heavy data lives here
    };

private:
    std::vector<NodeEntry> nodes;

    // Compilation Artifacts
    std::vector<NodeId> executionOrder;
    std::vector<uint32_t> initialFanOut; // ref_counts per node output

public:
    // ... addNode and addEdge (same as before) ...

    void compile() {
        const size_t count = nodes.size();
        executionOrder.clear();
        executionOrder.reserve(count);
        initialFanOut.assign(count, 0);

        // 1. Calculate In-Degrees (for Kahn's) and Fan-Outs (for Memory Management)
        std::vector<uint32_t> inDegree(count, 0);
        // Adjacency: Producer -> vector<ConsumerID>
        std::vector<std::vector<NodeId>> adj(count);

        for (NodeId i = 0; i < count; ++i) {
            for (const auto& conn : nodes[i].inputs) {
                if (conn.sourceNode != -1) { // Check valid
                    ++inDegree[i];
                    ++initialFanOut[conn.sourceNode]; // Count usage
                    adj[conn.sourceNode].push_back(i);
                }
            }
        }

        // 2. Optimization: Sort Adjacency List (Views BEFORE Mutators)
        // This ensures Views get scheduled first among siblings
        auto sorter = [&](NodeId a, NodeId b) {
            const bool a_is_view = std::visit([]<typename T0>(T0&& n) {
                return is_read_only<std::decay_t<T0>>::value;
            }, nodes[a].node);

            const bool b_is_view = std::visit([]<typename T0>(T0&& n) {
                return is_read_only<std::decay_t<T0>>::value;
            }, nodes[b].node);

            // True (View) comes before False (Mutator)
            return a_is_view > b_is_view;
        };

        for (auto& consumers : adj) {
            std::sort(consumers.begin(), consumers.end(), sorter);
        }

        // 3. Kahn's Topological Sort
        std::vector<NodeId> queue;
        for (NodeId i = 0; i < count; ++i) {
            if (inDegree[i] == 0) queue.push_back(i);
        }

        // Use index to simulate queue pop to avoid moving elements
        size_t head = 0;
        while(head < queue.size()) {
            NodeId u = queue[head++];
            executionOrder.push_back(u);

            // Because 'adj' is sorted (Views first), we push Views to the queue first
            for (NodeId v : adj[u]) {
                --inDegree[v];
                if (inDegree[v] == 0) {
                    queue.push_back(v);
                }
            }
        }

        if (executionOrder.size() != count) throw std::runtime_error("Cycle Detected");
    }

    void execute() {
        // 1. Runtime Ref Counting (Reset every run)
        // This vector is small (just uint32s), so allocation is cheap.
        // For max perf, keep this as a member variable and just re-assign.
        std::vector<uint32_t> liveRefCounts = initialFanOut;

        for (NodeId id : executionOrder) {
            auto& entry = nodes[id];

            // 2. Prepare Inputs with Move-on-Last Semantics
            std::vector<TValue> nodeInputs;
            nodeInputs.reserve(entry.inputs.size());

            for (const auto& conn : entry.inputs) {
                // Determine Source
                auto& sourceCache = nodes[conn.sourceNode].outputCache;
                auto& dataRef = sourceCache[conn.sourcePort];

                // Check refs
                // Decrement happens BEFORE usage check to see if we are the *last* one
                // (Assuming ref_count includes 'us')

                if (const uint32_t remaining = --liveRefCounts[conn.sourceNode]; remaining == 0) {
                    // Case: Last Consumer -> MOVE (Zero Copy)
                    // The sourceCache becomes invalid/empty after this, which is safe
                    // because count is 0.
                    nodeInputs.push_back(std::move(dataRef));
                } else {
                    // Case: Shared Data -> COPY
                    // We must clone because others need the original
                    nodeInputs.push_back(dataRef);
                }
            }

            // 3. Run Compute
            entry.outputCache = std::visit(
                [&](auto& n) { return n.compute(std::move(nodeInputs)); },
                entry.node
            );
        }
    }
};