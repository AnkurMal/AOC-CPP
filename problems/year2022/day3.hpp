#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace day3 {
    inline std::ifstream file{PATH "data/year2022/day3.txt"};

    inline auto priority = [](const char c) {
        if (std::islower(c)) return c - 'a' + 1;
        return c - 'A' + 27;
    };

    inline void part1() {
        std::string data;
        int sum{};

        while (std::getline(file, data)) {
            const auto len = data.size();
            auto c1 = data.substr(0, len / 2);
            auto c2 = data.substr(len / 2);

            for (auto &&i : c1)
                if (c2.contains(i)) {
                    sum += priority(i);
                    break;
                }
        }

        std::println("Part 1: {}", sum);
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};
        int sum{};
        const auto vec = data
                         | std::views::lazy_split('\n')
                         | std::ranges::to<std::vector<std::string>>();

        for (auto &&str : vec | std::views::chunk(3)) {
            for (const char c : str[0]) {
                if (str[1].contains(c) && str[2].contains(c)) {
                    sum += priority(c);
                    break;
                }
            }
        }

        std::println("Part 2: {}", sum);
    }
} // namespace day3
