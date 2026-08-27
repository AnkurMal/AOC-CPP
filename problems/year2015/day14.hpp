#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <string>
#include <ranges>
#include <vector>

#include <meta>
#include <format>
#include <print>
#include <string>

#define DERIVE_FORMAT(T)                                                       \
    namespace std {                                                            \
        template <>                                                            \
        struct formatter<T> {                                                  \
            constexpr auto parse(std::format_parse_context &ctx) {             \
                return ctx.begin();                                            \
            }                                                                  \
            auto format(const T &p, auto &ctx) const {                         \
                auto out = ctx.out();                                          \
                out = std::format_to(out, #T " {{");                           \
                bool first = true;                                             \
                template for (constexpr auto mem : std::define_static_array(   \
                                  std::meta::nonstatic_data_members_of(        \
                                      ^^T, std::meta::access_context::         \
                                               current()))) {                  \
                    if (!first) out = std::format_to(out, ", ");               \
                    first = false;                                             \
                    out = std::format_to(out, "{}: {}",                        \
                                         std::meta::identifier_of(mem),        \
                                         p.[:mem:]);                           \
                }                                                              \
                out = std::format_to(out, "}}");                               \
                return out;                                                    \
            }                                                                  \
        };                                                                     \
    }

using namespace std;

typedef struct {
    int speed, duration, rest;
} Reindeer;
DERIVE_FORMAT(Reindeer);

namespace day14 {
    ifstream file{PATH "/data/year2015/day14.txt"};
    string line;
    size_t tot{};

    void part1() {
        int second = 2503;
        int winner{};

        while (getline(file, line)) {
            auto spl = line | views::split(' ') | ranges::to<vector<string>>();
            int speed = stoi(spl[3]);
            int fly = stoi(spl[6]);
            int rest = stoi(spl[13]);

            int cycle = fly + rest;
            int full_cycles = second / cycle;
            int remaining = second % cycle;

            int distance = full_cycles * speed * fly;
            distance += min(remaining, fly) * speed;

            winner = max(winner, distance);
        }
        println("Part 1: {}", winner);
    }

    void part2() {
        int second = 2503;
        vector<Reindeer> vec;
        int winner{};

        while (getline(file, line)) {
            auto spl = line | views::split(' ') | ranges::to<vector<string>>();
            vec.push_back({stoi(spl[3]), stoi(spl[6]), stoi(spl[13])});
        }
        println("Part 1: {}", vec);
    }
} // namespace day14
