#pragma once

#include "path.hpp"
#include <cstddef>
#include <fstream>
#include <print>
#include <string>

using namespace std;

namespace day8 {
    ifstream file{PATH "/data/year2015/day8.txt"};
    string line;
    size_t tot{};

    void part1() {
        while (getline(file, line)) {
            size_t len{}, i{1};

            while (i < line.length() - 1) {
                len++;
                if (line[i] == '\\') {
                    if (line[i + 1] == 'x') i += 4;
                    else i += 2;
                } else {
                    i += 1;
                }
            }

            tot += line.length() - len;
        }

        println("Part 1: {}", tot);
    }

    void part2() {
        while (getline(file, line)) {
            size_t len{2};

            for (auto i : line) {
                if (i == '\"' || i == '\\') len += 2;
                else len += 1;
            }

            tot += len - line.length();
        }

        println("Part 2: {}", tot);
    }
} // namespace day8
