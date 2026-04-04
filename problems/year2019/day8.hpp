#pragma once

#include "path.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

namespace day8 {
    ifstream file{PATH "/data/year2019/day8.txt"};
    string data{istreambuf_iterator{file}, {}};
    string_view str{data};

    char get_pixel(vector<string_view> &vec, int column, int row = 0) {
        return (vec[row][column] == '2') ? get_pixel(vec, column, row + 1)
                                         : vec[row][column];
    }

    void part1() {
        int adv{25 * 6}, index{};
        auto min{INTMAX_MAX};

        for (int i = 0; i < str.length(); i += adv) {
            auto zero_count{ranges::count(str.substr(i, adv), '0')};
            if (zero_count < min) {
                min = zero_count;
                index = i;
            }
        }

        auto sub{str.substr(index, adv)};
        println("Part 1: {}",
                ranges::count(sub, '1') * ranges::count(sub, '2'));
    }

    void part2() {
        int wide{25}, adv{wide * 6};
        vector<string_view> vec;

        for (int i = 0; i < str.length(); i += adv)
            vec.emplace_back(str.substr(i, adv));

        println("Part 2: ");
        for (int i = 0; i < adv; i++) {
            if (i % wide == 0) println();
            char p{get_pixel(vec, i)};
            print("{}", (p == '1' ? "\u2591\u2591" : "  "));
        }
        println();
    }
} // namespace day8