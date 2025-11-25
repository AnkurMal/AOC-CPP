#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace day1 {
    inline std::ifstream file{PATH "data/year2022/day1.txt"};

    inline void part1() {
        std::string data{std::istreambuf_iterator{file}, {}};
        int max{};

        const auto vec = data
                         | std::views::lazy_split('\n')
                         | std::ranges::to<std::vector<std::string>>();

        int lsum{};
        for (auto &&i : vec) {
            if (i.empty()) {
                if (max < lsum) max = lsum;
                lsum = 0;
            } else lsum += std::stoi(i);
        }

        std::println("Part 1: {}", max);
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};
        std::vector<int> sum_vec;

        const auto vec = data
                         | std::views::lazy_split('\n')
                         | std::ranges::to<std::vector<std::string>>();

        int lsum{};
        for (auto &&i : vec) {
            if (i.empty()) {
                sum_vec.push_back(lsum);
                lsum = 0;
            } else lsum += std::stoi(i);
        }
        std::ranges::sort(sum_vec, std::greater{});

        std::println("Part 2: {}", sum_vec[0] + sum_vec[1] + sum_vec[2]);
    }
} // namespace day1
