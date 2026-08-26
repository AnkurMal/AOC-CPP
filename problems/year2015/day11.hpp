#pragma once

#include <print>
#include <string>
#include <ranges>
#include <unordered_map>

using namespace std;

namespace day11 {
    string data = "cqjxjnds";

    void next_password(int count) {
        int lc{};
        while (1) {
            int i = 7;
            if (data[7] == 'z')
                while (i >= 0 && data[i] == 'z') {
                    data[i] = 'a';
                    i--;
                }
            if (i >= 0) data[i]++;

            bool cond1 = !data.contains('i')
                         && !data.contains('l')
                         && !data.contains('o');
            bool cond2 = false;

            for (auto slide : data | views::slide(3)) {
                if (slide[1] - slide[0] == 1 && slide[2] - slide[1] == 1) {
                    cond2 = true;
                    break;
                }
            }

            int j{};
            unordered_map<char, int> map;
            while (j < data.size() - 1) {
                if (data[j] == data[j + 1]) {
                    map[data[j]]++;
                    j += 2;
                } else j++;
            }

            if (cond1 && cond2 && map.size() > 1) {
                lc++;
                if (lc == count) break;
            }
        }

        println("Part {}: {}", count, data);
    }

    void part1() { next_password(1); }

    void part2() { next_password(2); }
} // namespace day11
