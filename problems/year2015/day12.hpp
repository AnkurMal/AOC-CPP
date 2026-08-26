#pragma once

#include "path.hpp"
#include <fstream>
#include <print>
#include <regex>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;

namespace day12 {
    using json = nlohmann::json;

    ifstream file{PATH "/data/year2015/day12.txt"};
    string data{istreambuf_iterator{file}, {}};

    auto sum(const json &j) {
        if (j.is_number()) return j.get<long long>();

        if (j.is_array()) {
            long long total = 0;
            for (const auto &x : j)
                total += sum(x);
            return total;
        }

        if (j.is_object()) {
            for (const auto &[key, value] : j.items())
                if (value.is_string() && value == "red") return 0ll;

            long long total = 0;
            for (const auto &[key, value] : j.items())
                total += sum(value);

            return total;
        }

        return 0ll;
    }

    void part1() {
        regex re(R"(-?\d+)");
        smatch match;
        int sum{};

        while (regex_search(data, match, re)) {
            sum += stoi(match.str());
            data = match.suffix();
        }

        println("Part 1: {}", sum);
    }

    void part2() {
        json j = json::parse(data);
        println("Part 2: {}", sum(j));
    }
} // namespace day12
