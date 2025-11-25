#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <string>

namespace day1 {
    inline std::ifstream file{PATH "data/year2019/day1.txt"};

    inline void part1() {
        std::string data;
        int sum = 0;

        while (std::getline(file, data)) {
            sum += std::stoi(data) / 3 - 2;
        }

        std::println("Part 1: {}", sum);
    }

    inline void part2() {
        std::string data;
        int sum = 0;

        while (std::getline(file, data)) {
            auto num = std::stoi(data) / 3 - 2;

            while (num > 0) {
                sum += num;
                num = num / 3 - 2;
            }
        }

        std::println("Part 2: {}", sum);
    }
} // namespace day1
