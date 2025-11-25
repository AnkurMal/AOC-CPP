#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

inline auto get_data(std::ifstream &file) {
    std::string data{std::istreambuf_iterator{file}, {}};
    return data
           | std::views::lazy_split(',')
           | std::views::transform([](auto &&rng) {
                 auto x = rng | std::views::common;
                 return std::stoi(std::string{x.begin(), x.end()});
             })
           | std::ranges::to<std::vector>();
}

namespace day2 {
    inline std::ifstream file{PATH "data/year2019/day2.txt"};

    inline void part1() {
        auto vec = get_data(file);

        vec[1] = 12;
        vec[2] = 2;

        int i = 0;
        while (vec[i] != 99) {
            if (vec[i] == 1) {
                vec[vec[i + 3]] = vec[vec[i + 1]] + vec[vec[i + 2]];
                i += 4;
            } else if (vec[i] == 2) {
                vec[vec[i + 3]] = vec[vec[i + 1]] * vec[vec[i + 2]];
                i += 4;
            } else i++;
        }

        std::println("Part 1: {}", vec[0]);
    }

    inline void part2() {
        const auto list = get_data(file);

        for (int x = 0; x <= 99; x++) {
            for (int y = 0; y <= 99; y++) {
                auto vec = list;
                vec[1] = x;
                vec[2] = y;

                int i = 0;
                while (vec[i] != 99) {
                    if (vec[i] == 1) {
                        vec[vec[i + 3]] = vec[vec[i + 1]] + vec[vec[i + 2]];
                        i += 4;
                    } else if (vec[i] == 2) {
                        vec[vec[i + 3]] = vec[vec[i + 1]] * vec[vec[i + 2]];
                        i += 4;
                    } else i++;
                }

                if (vec[0] == 19690720) {
                    std::println("Part 2: {}", 100 * vec[1] + vec[2]);
                    return;
                }
            }
        }
    }
} // namespace day2
