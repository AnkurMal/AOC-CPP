#pragma once

#include "intcode.hpp"
#include "path.hpp"
#include <fstream>
#include <print>

namespace day2 {
    inline std::ifstream file{PATH "data/year2019/day2.txt"};

    inline void part1() {
        auto vec = get_data(file);

        vec[1] = 12;
        vec[2] = 2;

        intcode(vec);
        std::println("Part 1: {}", vec[0]);
    }

    inline void part2() {
        const auto list = get_data(file);

        for (int x = 0; x <= 99; x++) {
            for (int y = 0; y <= 99; y++) {
                auto vec = list;
                vec[1] = x;
                vec[2] = y;

                intcode(vec);
                if (vec[0] == 19690720) {
                    std::println("Part 2: {}", 100 * vec[1] + vec[2]);
                    return;
                }
            }
        }
    }
} // namespace day2
