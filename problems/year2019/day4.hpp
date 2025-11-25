#pragma once

#include "path.hpp"
#include <print>

namespace day4 {
    inline void part1() {
        auto counter{0};

        for (int i = 153517; i < 630395; i++) {
            auto num = i;
            auto same{false};
            auto last = num % 10;

            while (num != 0) {
                num /= 10;
                const auto curr = num % 10;

                if (last < curr) goto outer;
                if (last == curr) same = true;
                last = curr;
            }

            if (same) counter++;

        outer:;
        }

        std::println("Part 1: {}", counter);
    }

    inline void part2() {
        auto counter{0};

        for (int i = 153517; i < 630395; i++) {
            auto num = i;
            auto same{false};
            int last = num % 10, twoCounter = 1;

            while (num != 0) {
                num /= 10;
                const auto curr = num % 10;

                if (last < curr) goto outer;
                if (last == curr) twoCounter++;
                else {
                    if (twoCounter == 2) same = true;
                    twoCounter = 1;
                }

                last = curr;
            }

            if (same) counter++;

        outer:;
        }

        std::println("Part 2: {}", counter);
    }
} // namespace day4
