#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace day5 {
    inline std::ifstream file{PATH "data/year2020/day5.txt"};

    inline void part1() {
        std::string data;
        int max{};

        while (std::getline(file, data)) {
            std::pair row{0, 127};
            std::pair column{0, 7};

            for (size_t i = 0; i < 7; i++) {
                if (data[i] == 'F') {
                    row.second = (row.first + row.second - 1) / 2;
                } else {
                    row.first = (row.first + row.second + 1) / 2;
                }
            }

            for (size_t i = 7; i < data.size(); i++) {
                if (data[i] == 'L') {
                    column.second = (column.first + column.second - 1) / 2;
                } else {
                    column.first = (column.first + column.second + 1) / 2;
                }
            }

            const auto id = row.first * 8 + column.first;
            if (max < id) max = id;
        }

        std::println("Part 1: {}", max);
    }

    inline void part2() {
        std::string data;
        std::vector<int> vec;

        while (std::getline(file, data)) {
            std::pair row{0, 127};
            std::pair column{0, 7};

            for (size_t i = 0; i < 7; i++) {
                if (data[i] == 'F') {
                    row.second = (row.first + row.second - 1) / 2;
                } else {
                    row.first = (row.first + row.second + 1) / 2;
                }
            }

            for (size_t i = 7; i < data.size(); i++) {
                if (data[i] == 'L') {
                    column.second = (column.first + column.second - 1) / 2;
                } else {
                    column.first = (column.first + column.second + 1) / 2;
                }
            }

            const auto id = row.first * 8 + column.first;
            vec.push_back(id);
        }

        std::ranges::sort(vec);
        for (auto &&[a, b] : std::views::zip(vec, std::views::drop(vec, 1))) {
            if (b - a == 2) {
                std::println("Part 2: {}", a + 1);
                return;
            }
        }
    }
} // namespace day5
