#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace day4 {
    inline std::ifstream file{PATH "data/year2022/day4.txt"};

    inline void part1() {
        std::string data;
        int count{};

        while (std::getline(file, data)) {
            auto spl1 = data
                        | std::views::lazy_split(',')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl2 = spl1[0]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl3 = spl1[1]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            const std::pair p1{std::stoi(spl2[0]), std::stoi(spl2[1])};
            const std::pair p2{std::stoi(spl3[0]), std::stoi(spl3[1])};

            if ((p1.first <= p2.first && p1.second >= p2.second)
                || (p2.first <= p1.first && p2.second >= p1.second))
                count++;
        }

        std::println("Part 1: {}", count);
    }

    inline void part2() {
        std::string data;
        int count{};

        while (std::getline(file, data)) {
            auto spl1 = data
                        | std::views::lazy_split(',')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl2 = spl1[0]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl3 = spl1[1]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            const std::pair p1{std::stoi(spl2[0]), std::stoi(spl2[1])};
            const std::pair p2{std::stoi(spl3[0]), std::stoi(spl3[1])};

            if (p1.first <= p2.second && p2.first <= p1.second) count++;
        }

        std::println("Part 2: {}", count);
    }
} // namespace day4
