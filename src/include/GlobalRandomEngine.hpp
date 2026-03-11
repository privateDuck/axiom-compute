#pragma once

#include <cstdint>
#include <random>

class GlobalRandomEngine {
public:
    static GlobalRandomEngine& getInstance() {
        static GlobalRandomEngine instance;
        return instance;
    }

    std::mt19937_64& getRandomEngine() { return rng; }

    void SetSeed(const int64_t seed) {
        rng.seed(seed);
    }

    void SetRandomSeed() {
        rng.seed(rd());
    }

    GlobalRandomEngine(const GlobalRandomEngine&) = delete;
    GlobalRandomEngine& operator=(const GlobalRandomEngine&) = delete;
    GlobalRandomEngine(GlobalRandomEngine&&) = delete;
    GlobalRandomEngine& operator=(GlobalRandomEngine&&) = delete;

private:
    GlobalRandomEngine() : rng(rd()) {}

    std::random_device rd;
    std::mt19937_64 rng;

};