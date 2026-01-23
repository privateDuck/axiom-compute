//
// Created by Tharuka on 23/01/2026.
//

#ifndef ATLAS_COMPUTEGRAPH_HPP
#define ATLAS_COMPUTEGRAPH_HPP
#pragma once

#include "TrainNodes/TrainNodeBase.hpp"
#include "nlohmann/json.hpp"

class ComputeGraph {
public:
    bool BuildGraph(const nlohmann::json& blueprint) {

    }
private:
    std::vector<std::unique_ptr<TrainNodeBase>> dpl_nodes; // Data pipeline nodes
};

#endif //ATLAS_COMPUTEGRAPH_HPP