#pragma once

#include "path.hpp"
#include <algorithm>
#include <climits>
#include <fstream>
#include <print>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace day9 {
    ifstream file{PATH "/data/year2015/day9.txt"};
    string line;

    auto distance(bool mx) {
        vector<string> cities;
        map<pair<string, string>, int> dis;
        int ans = mx ? INT_MIN : INT_MAX;

        regex re(R"((\w+) to (\w+) = (\d+))");
        smatch match;

        while (getline(file, line)) {
            regex_match(line, match, re);
            string c1 = match[1];
            string c2 = match[2];
            int dist = stoi(match[3]);

            if (!ranges::contains(cities, c1)) cities.push_back(c1);
            if (!ranges::contains(cities, c2)) cities.push_back(c2);
            dis[{c1, c2}] = dist;
            dis[{c2, c1}] = dist;
        }

        ranges::sort(cities);
        do {
            int total = 0;

            for (int i = 1; i < cities.size(); ++i)
                total += dis[{cities[i - 1], cities[i]}];

            ans = mx ? max(ans, total) : min(ans, total);
        } while (ranges::next_permutation(cities).found);

        return ans;
    }

    void part1() { println("Part 1: {}", distance(false)); }

    void part2() { println("Part 2: {}", distance(true)); }
} // namespace day9
