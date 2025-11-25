#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>

namespace day1 {
    inline std::ifstream file{PATH "data/year2020/day1.txt"};

    inline void part1() {
        std::string data{std::istreambuf_iterator{file}, {}};

        auto vec = data
                   | std::views::lazy_split('\n')
                   | std::views::transform([](auto &&rng) {
                         auto x = rng | std::views::common;
                         auto str = std::string{x.begin(), x.end()};
                         return std::stoi(std::string{x.begin(), x.end()});
                     });

        for (auto &&i : vec) {
            for (auto &&j : vec | std::views::drop(1)) {
                if (i + j == 2020) {
                    std::println("Part 1: {}", i * j);
                    return;
                }
            }
        }
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};

        auto vec = data
                   | std::views::lazy_split('\n')
                   | std::views::transform([](auto &&rng) {
                         auto x = rng | std::views::common;
                         auto str = std::string{x.begin(), x.end()};
                         return std::stoi(std::string{x.begin(), x.end()});
                     });

        for (auto &&i : vec) {
            for (auto &&j : vec | std::views::drop(1)) {
                for (auto &&k : vec | std::views::drop(2)) {
                    if (i + j + k == 2020) {
                        std::println("Part 2: {}", i * j * k);
                        return;
                    }
                }
            }
        }
    }
} // namespace day1
