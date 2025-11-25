#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace day2 {
    using namespace std::literals;
    inline std::ifstream file{PATH "data/year2020/day2.txt"};

    inline void part1() {
        std::string data;
        int counter{};

        while (std::getline(file, data)) {
            auto spl1 = data
                        | std::views::lazy_split(": "sv)
                        | std::ranges::to<std::vector<std::string>>();

            auto spl2 = spl1[0]
                        | std::views::lazy_split(' ')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl3 = spl2[0]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            const std::pair range{std::stoi(spl3[0]), std::stoi(spl3[1])};
            const int count
                = static_cast<int>(std::ranges::count(spl1[1], spl2[1][0]));

            if (count >= range.first && count <= range.second) counter++;
        }

        std::println("Part 1: {}", counter);
    }

    inline void part2() {
        std::string data;
        int counter{};

        while (std::getline(file, data)) {
            auto spl1 = data
                        | std::views::lazy_split(": "sv)
                        | std::ranges::to<std::vector<std::string>>();

            auto spl2 = spl1[0]
                        | std::views::lazy_split(' ')
                        | std::ranges::to<std::vector<std::string>>();

            auto spl3 = spl2[0]
                        | std::views::lazy_split('-')
                        | std::ranges::to<std::vector<std::string>>();

            const std::pair range{std::stoi(spl3[0]) - 1,
                                  std::stoi(spl3[1]) - 1};
            auto str{std::move(spl1[1])};
            const auto ch{spl2[1][0]};

            if ((str[range.first] != ch && str[range.second] == ch)
                || (str[range.first] == ch && str[range.second] != ch))
                counter++;
        }

        std::println("Part 2: {}", counter);
    }
} // namespace day2
