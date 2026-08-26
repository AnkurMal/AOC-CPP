#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <map>
#include <print>
#include <string>
#include <utility>
#include <vector>
#include <ranges>

using namespace std;

namespace day13 {
    ifstream file{PATH "/data/year2015/day13.txt"};
    string line;

    auto happy_points(bool me) {
        map<pair<string, string>, int> map;
        vector<string> names;
        int points = 0;

        while (getline(file, line)) {
            auto spl = line | views::split(' ') | ranges::to<vector<string>>();
            if (!ranges::contains(names, spl[0])) names.push_back(spl[0]);

            int pts = stoi(spl[3]) * ((spl[2] == "gain") ? 1 : -1);
            map[{spl[0], spl[10].substr(0, spl[10].size() - 1)}] = pts;
            if (me) {
                map[{"me", spl[0]}] = 0;
                map[{spl[0], "me"}] = 0;
            }
        }
        if (me) names.push_back("me");
        int len = names.size();

        ranges::sort(names);
        do {
            int lp{};

            for (int i = 0; i < names.size(); i++) {
                string prev = names[(i - 1 + len) % len],
                       next = names[(i + 1) % len];

                lp += map[{names[i], prev}] + map[{names[i], next}];
            }
            points = max(points, lp);
        } while (ranges::next_permutation(names).found);

        return points;
    }

    void part1() { println("Part 1: {}", happy_points(false)); }

    void part2() { println("Part 2: {}", happy_points(true)); }
} // namespace day13
