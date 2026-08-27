#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <string>
#include <ranges>
#include <vector>

using namespace std;

typedef struct {
    int speed, duration, rest, passed, total, points;
    bool brest;

} Reindeer;

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

        while (getline(file, line)) {
            auto spl = line | views::split(' ') | ranges::to<vector<string>>();
            vec.push_back(
                {stoi(spl[3]), stoi(spl[6]), stoi(spl[13]), stoi(spl[6])});
        }

        for (int j = 0; j < second; j++) {
            for (auto &i : vec) {
                i.passed--;
                if (!i.brest) i.total += i.speed;

                if (i.passed == 0) {
                    i.passed = (i.brest) ? i.duration : i.rest;
                    i.brest = !i.brest;
                }
            }

            auto mx = ranges::max(vec, {}, &Reindeer::total);
            for (auto &i : vec) {
                if (i.total == mx.total) i.points++;
            }
        }

        auto mx = ranges::max(vec, {}, &Reindeer::points);
        println("Part 2: {}", mx.points);
    }
} // namespace day14
