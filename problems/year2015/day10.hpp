#pragma once

#include <print>
#include <string>
#include <utility>

using namespace std;

namespace day10 {
    string data = "1113222113";

    auto count_say(int count) {
        for (int j = 0; j < count; j++) {
            string ne{};
            int count{};
            char curr = data[0];

            for (auto i : data) {
                if (i == curr) count++;
                else {
                    ne += to_string(count) + curr;
                    count = 1;
                    curr = i;
                }
            }

            ne += to_string(count) + curr;
            data = std::move(ne);
        }

        return data.size();
    }

    void part1() { println("Part 1: {}", count_say(40)); }

    void part2() { println("Part 1: {}", count_say(50)); }
} // namespace day10
