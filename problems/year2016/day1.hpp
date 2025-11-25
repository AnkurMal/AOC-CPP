#pragma once

#include "path.hpp"
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <string>
#include <vector>

enum Direction { NORTH, SOUTH, EAST, WEST };

namespace day1 {
    using namespace std::literals;
    inline std::ifstream file{PATH "data/year2016/day1.txt"};

    inline void part1() {
        const std::string data(std::istreambuf_iterator(file), {});
        std::pair coord{0, 0};
        auto direction{Direction::NORTH};

        const auto spl = data
                         | std::views::lazy_split(", "sv)
                         | std::ranges::to<std::vector<std::string>>();

        for (auto &i : spl) {
            const auto num = std::stoi(i.substr(1));

            if (direction == NORTH) {
                if (i[0] == 'L') {
                    direction = WEST;
                    coord.first -= num;
                } else {
                    direction = EAST;
                    coord.first += num;
                }
            } else if (direction == EAST) {
                if (i[0] == 'L') {
                    direction = NORTH;
                    coord.second += num;
                } else {
                    direction = SOUTH;
                    coord.second -= num;
                }
            } else if (direction == SOUTH) {
                if (i[0] == 'L') {
                    direction = EAST;
                    coord.first += num;
                } else {
                    direction = WEST;
                    coord.first -= num;
                }
            } else {
                if (i[0] == 'L') {
                    direction = SOUTH;
                    coord.second -= num;
                } else {
                    direction = NORTH;
                    coord.second += num;
                }
            }
        }

        const auto x = std::abs(coord.first);
        const auto y = std::abs(coord.second);
        std::println("Part 1: {}", x + y);
    }
} // namespace day1