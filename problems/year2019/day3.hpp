#pragma once

#include "derive_format.hpp"
#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

struct Steps {
    std::pair<int, int> pair;
    int distance;
};
DERIVE_FORMAT(Steps);

inline auto update_coord(std::pair<int, int> &pair, const std::string &str) {
    if (str[0] == 'R') pair.first += std::stoi(str.substr(1));
    else if (str[0] == 'U') pair.second += std::stoi(str.substr(1));
    else if (str[0] == 'L') pair.first -= std::stoi(str.substr(1));
    else pair.second -= std::stoi(str.substr(1));
}

namespace day3 {
    inline std::ifstream file{PATH "data/year2019/day3.txt"};

    inline void part1() {
        std::string data{std::istreambuf_iterator{file}, {}};

        const auto list
            = data
              | std::views::lazy_split('\n')
              | std::views::transform([](auto &&rng) {
                    auto x = rng | std::views::common;

                    return std::string{x.begin(), x.end()}
                           | std::views::lazy_split(',')
                           | std::ranges::to<std::vector<std::string>>();
                })
              | std::ranges::to<std::vector>();

        std::vector<std::pair<int, int>> first{{0, 0}};
        for (auto &i : list[0]) {
            auto last = first.back();
            update_coord(last, i);

            first.push_back(last);
        }

        std::pair second1{0, 0};
        std::vector<std::pair<int, int>> cross;

        for (auto &i : list[1]) {
            std::pair second2{second1};
            update_coord(second2, i);

            for (size_t j = 0; j < first.size() - 1; j++) {
                if (first[j].second
                    == first[j + 1].second
                    && second1.first
                    == second2.first) {

                    std::array rng1{first[j].first, first[j + 1].first};
                    std::array rng2{second1.second, second2.second};

                    std::ranges::sort(rng1);
                    std::ranges::sort(rng2);

                    if ((second1.first > rng1[0] && second1.first < rng1[1])
                        && (first[j].second
                            > rng2[0]
                            && first[j].second
                            < rng2[1])) {
                        cross.push_back({second1.first, first[j].second});
                    }
                } else if (first[j].first
                           == first[j + 1].first
                           && second1.second
                           == second2.second) {

                    std::array rng1{first[j].second, first[j + 1].second};
                    std::array rng2{second1.first, second2.first};

                    std::ranges::sort(rng1);
                    std::ranges::sort(rng2);

                    if ((second1.second > rng1[0] && second1.second < rng1[1])
                        && (first[j].first
                            > rng2[0]
                            && first[j].first
                            < rng2[1])) {
                        cross.push_back({first[j].first, second1.second});
                    }
                }
            }
            second1 = second2;
        }

        auto res = cross
                   | std::views::transform(
                       [](auto &&x) { return abs(x.first) + abs(x.second); })
                   | std::ranges::to<std::vector>();

        std::println("Part 1: {}", std::ranges::min(res));
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};

        const auto list
            = data
              | std::views::lazy_split('\n')
              | std::views::transform([](auto &&rng) {
                    auto x = rng | std::views::common;

                    return std::string{x.begin(), x.end()}
                           | std::views::lazy_split(',')
                           | std::ranges::to<std::vector<std::string>>();
                })
              | std::ranges::to<std::vector>();

        std::vector<std::pair<int, int>> first{{0, 0}};
        for (auto &i : list[0]) {
            auto last = first.back();
            update_coord(last, i);
            first.push_back(last);
        }

        std::pair second1{0, 0};
        std::vector<Steps> cross;

        int wire2_steps = 0;
        for (auto &i : list[1]) {
            std::pair second2{second1};
            update_coord(second2, i);
            const int seg2_len = std::abs(second2.first - second1.first)
                                 + std::abs(second2.second - second1.second);

            int wire1_steps = 0;
            for (size_t j = 0; j < first.size() - 1; j++) {
                const auto p1 = first[j];
                const auto p2 = first[j + 1];
                const int seg1_len = std::abs(p2.first - p1.first)
                                     + std::abs(p2.second - p1.second);

                if (p1.second == p2.second && second1.first == second2.first) {
                    std::array rng1{p1.first, p2.first};
                    std::array rng2{second1.second, second2.second};
                    std::ranges::sort(rng1);
                    std::ranges::sort(rng2);

                    if ((second1.first > rng1[0] && second1.first < rng1[1])
                        && (p1.second > rng2[0] && p1.second < rng2[1])) {
                        int ix = second1.first;
                        int iy = p1.second;

                        const int total = wire1_steps
                                          + std::abs(ix - p1.first)
                                          + wire2_steps
                                          + std::abs(iy - second1.second);
                        cross.push_back({{ix, iy}, total});
                    }
                } else if (p1.first
                           == p2.first
                           && second1.second
                           == second2.second) {
                    std::array rng1{p1.second, p2.second};
                    std::array rng2{second1.first, second2.first};
                    std::ranges::sort(rng1);
                    std::ranges::sort(rng2);

                    if ((second1.second > rng1[0] && second1.second < rng1[1])
                        && (p1.first > rng2[0] && p1.first < rng2[1])) {
                        int ix = p1.first;
                        int iy = second1.second;
                        const int total = wire1_steps
                                          + std::abs(iy - p1.second)
                                          + wire2_steps
                                          + std::abs(ix - second1.first);
                        cross.push_back({{ix, iy}, total});
                    }
                }
                wire1_steps += seg1_len;
            }
            wire2_steps += seg2_len;
            second1 = second2;
        }

        std::erase_if(cross, [](auto &s) {
            return s.pair.first == 0 && s.pair.second == 0;
        });

        const auto min = std::ranges::min_element(cross, {}, &Steps::distance);
        std::println("Part 2: {}", min->distance);
    }

} // namespace day3
