#pragma once

#include "intcode.hpp"
#include "path.hpp"
#include <fstream>
#include <print>

namespace day9 {
    inline std::ifstream file{PATH "/data/year2019/day9.txt"};

    inline void part1() {
        auto vec = get_data(file);

        std::println("Part 1: {}", intcode(vec, 1));
    }

    inline void part2() {
        auto vec = get_data(file);

        std::println("Part 2: {}", intcode(vec, 2));
    }
} // namespace day9
