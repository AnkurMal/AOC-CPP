#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <string>

inline auto get_win_hand(const char op_move) {
    if (op_move == 'A') return 'Y';
    if (op_move == 'B') return 'Z';
    return 'X';
}

inline auto get_draw_hand(const char op_move) {
    if (op_move == 'A') return 'X';
    if (op_move == 'B') return 'Y';
    return 'Z';
}

inline auto get_loose_hand(const char op_move) {
    if (op_move == 'A') return 'Z';
    if (op_move == 'B') return 'X';
    return 'Y';
}

inline auto get_score(const char move) {
    if (move == 'X') return 1;
    if (move == 'Y') return 2;
    return 3;
}

namespace day2 {
    inline std::ifstream file{PATH "data/year2022/day2.txt"};

    inline void part1() {
        std::string data;
        int score{};

        while (std::getline(file, data)) {
            if (data[2] == get_win_hand(data[0]))
                score += get_score(data[2]) + 6;
            else if (data[2] == get_draw_hand(data[0]))
                score += get_score(data[2]) + 3;
            else score += get_score(data[2]);
        }

        std::println("Part 1: {}", score);
    }

    inline void part2() {
        std::string data;
        int score{};

        while (std::getline(file, data)) {
            if (data[2] == 'Y') score += get_score(get_draw_hand(data[0])) + 3;
            else if (data[2] == 'Z')
                score += get_score(get_win_hand(data[0])) + 6;
            else score += get_score(get_loose_hand(data[0]));
        }

        std::println("Part 2: {}", score);
    }
} // namespace day2
