#pragma once

#include "common.hpp"
#include "path.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

namespace day7 {
    ifstream file{PATH "/data/year2015/day7.txt"};
    string str{istreambuf_iterator{file}, {}};

    auto get_index(vector<vector<string_view>> &spl, string_view search) {
        for (size_t i = 0; i < spl.size(); i++) {
            if (spl[i].back() == search) {
                return i;
            }
        }
        return 0ull;
    }

    uint16_t get_value(vector<vector<string_view>> &spl, string_view search,
                       unordered_map<string_view, uint16_t> &map) {
        if (map.contains(search)) return map[search];
        else {
            uint16_t ans{};
            auto &vec{spl[get_index(spl, search)]};

            if (vec.size() == 3) {
                if (is_digit(vec[0])) parse_digit(vec[0], ans);
                else ans = get_value(spl, vec[0], map);
            } else if (vec.size() == 5) {
                uint16_t a1{}, a2{};

                if (is_digit(vec[0])) parse_digit(vec[0], a1);
                else a1 = get_value(spl, vec[0], map);

                if (is_digit(vec[2])) parse_digit(vec[2], a2);
                else a2 = get_value(spl, vec[2], map);

                if (vec[1] == "AND") ans = a1 & a2;
                else if (vec[1] == "OR") ans = a1 | a2;
                else if (vec[1] == "LSHIFT") ans = a1 << a2;
                else ans = a1 >> a2;
            } else {
                if (is_digit(vec[1])) parse_digit(vec[1], ans);
                else ans = ~get_value(spl, vec[1], map);
            }

            map[search] = ans;
            return ans;
        }
    }

    auto get_split() {
        return str
               | views::split('\n')
               | views::transform([](auto &&x) {
                     return x
                            | views::split(' ')
                            | views::transform(
                                [](auto &&y) { return string_view{y}; })
                            | ranges::to<vector>();
                 })
               | ranges::to<vector>();
    }

    void part1() {
        auto spl{get_split()};
        unordered_map<string_view, uint16_t> map;

        println("Part 1: {}", get_value(spl, "a", map));
    }

    void part2() {
        auto spl{get_split()};
        unordered_map<string_view, uint16_t> map;

        auto val_a{get_value(spl, "a", map)};
        map.clear();

        auto idx_b{get_index(spl, "b")};
        auto override_str{to_string(val_a)};
        spl[idx_b] = {override_str, "->", "b"};

        println("Part 2: {}", get_value(spl, "a", map));
    }
} // namespace day7
