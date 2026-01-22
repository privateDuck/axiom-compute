//
// Created by Tharuka on 23/01/2026.
//

#ifndef ATLAS_TRAINNODEBASE_HPP
#define ATLAS_TRAINNODEBASE_HPP

#pragma once

#include <vector>
#include <array>
#include <memory>
#include <cstdint>

class TrainNodeBase {
public:
    uint32_t id;
    std::array<std::unique_ptr<DataFrame>, 3> inputs;

    struct Connection {
        TrainNodeBase* target_node;
        int target_port;
    };

    std::vector<Connection> successors;

};

#endif //ATLAS_TRAINNODEBASE_HPP