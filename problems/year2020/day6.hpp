#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace day6 {
    inline std::ifstream file{PATH "data/year2020/day6.txt"};

    inline void part1() {
        std::string data;
        std::unordered_set<int> set;
        size_t sum{};

        while (std::getline(file, data)) {
            if (data.empty()) {
                sum += set.size();
                set.clear();
            }

            for (const char ch : data) {
                set.insert(ch);
            }
        }

        sum += set.size();
        std::println("Part 1: {}", sum);
    }

    inline void part2() {
        std::string data;
        std::unordered_map<char, int> map;
        size_t sum{};
        int row{};

        while (std::getline(file, data)) {
            if (data.empty()) {
                for (const auto &val : map | std::views::values) {
                    if (val == row) sum++;
                }

                map.clear();
                row = -1;
            }

            for (const char ch : data) {
                map[ch]++;
            }
            row++;
        }

        for (const auto &val : map | std::views::values) {
            if (val == row) sum++;
        }
        std::println("Part 2: {}", sum);
    }
} // namespace day6
