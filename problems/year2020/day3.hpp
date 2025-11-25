#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace day3 {
    inline std::ifstream file{PATH "data/year2020/day3.txt"};

    inline void part1() {
        std::string data{std::istreambuf_iterator{file}, {}};

        const auto vec = data
                         | std::views::lazy_split('\n')
                         | std::ranges::to<std::vector<std::string>>();

        std::pair<size_t, size_t> coord{3, 1};
        int count{0};

        while (coord.second < vec.size()) {
            if (vec[coord.second][coord.first] == '#') count++;
            coord.second++;
            coord.first = (coord.first + 3) % vec[0].size();
        }

        std::println("Part 1: {}", count);
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};

        const auto vec = data
                         | std::views::lazy_split('\n')
                         | std::ranges::to<std::vector<std::string>>();

        const std::vector<std::pair<size_t, size_t>> slopes{
            {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
        long long res{1};

        for (auto &&slp : slopes) {
            std::pair coord{slp};
            long long count{0};

            while (coord.second < vec.size()) {
                if (vec[coord.second][coord.first] == '#') count++;
                coord.second += slp.second;
                coord.first = (coord.first + slp.first) % vec[0].size();
            }

            res *= count;
        }

        std::println("Part 2: {}", res);
    }
} // namespace day3
