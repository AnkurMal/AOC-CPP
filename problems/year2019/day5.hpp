#pragma once

#include "day2.hpp"
#include "path.hpp"
#include <fstream>
#include <print>
#include <vector>

inline auto get_value(const std::vector<int> &vec, const int mode,
                      const int pos) {
    const int size = vec.size();

    if (pos >= size) return 0;
    else if (mode == 0) {
        return (vec[pos] < size) ? vec[vec[pos]] : 0;
    } else return vec[pos];
}

namespace day5 {
    inline std::ifstream file{PATH "/data/year2019/day5.txt"};

    inline void part1() {
        auto vec = get_data(file);

        int i{}, opcode, output{};
        while ((opcode = vec[i] % 100) != 99) {
            const auto m1{vec[i] / 100 % 10};
            const auto m2{vec[i] / 1000 % 10};

            const auto v1 = get_value(vec, m1, i + 1);
            const auto v2 = get_value(vec, m2, i + 2);

            switch (opcode) {
            case 1:
                vec[vec[i + 3]] = v1 + v2;
                i += 4;
                break;

            case 2:
                vec[vec[i + 3]] = v1 * v2;
                i += 4;
                break;

            case 3:
                vec[vec[i + 1]] = 1;
                i += 2;
                break;

            case 4:
                output = v1;
                i += 2;
                break;

            default:
                i++;
            }
        }

        std::println("Part 1: {}", output);
    }

    inline void part2() {
        auto vec = get_data(file);

        int i{}, opcode, output{};
        while ((opcode = vec[i] % 100) != 99) {
            const auto m1{vec[i] / 100 % 10};
            const auto m2{vec[i] / 1000 % 10};

            const auto v1 = get_value(vec, m1, i + 1);
            const auto v2 = get_value(vec, m2, i + 2);

            switch (opcode) {
            case 1:
                vec[vec[i + 3]] = v1 + v2;
                i += 4;
                break;

            case 2:
                vec[vec[i + 3]] = v1 * v2;
                i += 4;
                break;

            case 3:
                vec[vec[i + 1]] = 5;
                i += 2;
                break;

            case 4:
                output = v1;
                i += 2;
                break;

            case 5:
                if (v1 != 0) i = v2;
                else i += 3;
                break;

            case 6:
                if (v1 == 0) i = v2;
                else i += 3;
                break;

            case 7:
                vec[vec[i + 3]] = v1 < v2;
                i += 4;
                break;

            case 8:
                vec[vec[i + 3]] = v1 == v2;
                i += 4;
                break;

            default:
                i++;
            }
        }

        std::println("Part 2: {}", output);
    }
} // namespace day5
