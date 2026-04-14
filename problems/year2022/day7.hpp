#pragma once

#include "path.hpp"
#include <charconv>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

namespace day7 {
    ifstream file{PATH "/data/year2022/day7.txt"};
    string data{istreambuf_iterator{file}, {}};

    size_t
    get_size(const fs::path &path,
             unordered_map<fs::path, vector<variant<fs::path, size_t>>> &map,
             unordered_map<fs::path, size_t> &memo) {
        if (memo.contains(path)) return memo[path];
        else {
            size_t size{};

            for (auto &i : map[path]) {
                if (holds_alternative<size_t>(i)) size += get<size_t>(i);
                else {
                    auto dir{path / get<fs::path>(i)};
                    size += get_size(dir, map, memo);
                }
            }

            memo[path] = size;
            return size;
        }
    }

    auto get_spl() {
        return data
               | views::split('\n')
               | views::transform([](auto &&line) {
                     return line
                            | views::split(' ')
                            | views::transform(
                                [](auto &&x) { return string_view{x}; })
                            | ranges::to<vector>();
                 })
               | ranges::to<vector>();
    }

    void
    init_map(vector<vector<string_view>> &spl, fs::path &path,
             unordered_map<fs::path, vector<variant<fs::path, size_t>>> &map) {
        size_t i{};

        while (i < spl.size()) {
            auto &curr{spl[i]};

            if (curr[0] == "$") {
                if (curr[1] == "cd") {
                    if (curr[2] == "..") path = path.parent_path();
                    else path /= curr[2];

                    i++;
                } else {
                    i++;
                    while (i < spl.size() && spl[i][0] != "$") {
                        auto &str{spl[i]};

                        if (str[0] == "dir") map[path].push_back(str[1]);
                        else {
                            size_t size;
                            from_chars(str[0].data(),
                                       str[0].data() + str[0].size(), size);
                            map[path].push_back(size);
                        }

                        i++;
                    }
                }
            }
        }
    }

    void part1() {
        fs::path path;
        unordered_map<fs::path, vector<variant<fs::path, size_t>>> map;

        auto spl{get_spl()};
        init_map(spl, path, map);

        size_t sum{};
        unordered_map<fs::path, size_t> memo;

        for (auto &key : map | views::keys) {
            auto size{get_size(key, map, memo)};
            if (size < 100000) sum += size;
        }

        println("Part 1: {}", sum);
    }

    void part2() {
        fs::path path;
        unordered_map<fs::path, vector<variant<fs::path, size_t>>> map;

        auto spl{get_spl()};
        init_map(spl, path, map);

        unordered_map<fs::path, size_t> memo;

        auto size{30000000 - (70000000 - get_size("/", map, memo))};
        auto best{memo["/"]};

        for (auto i : memo | views::values)
            if (i >= size && i < best) best = i;

        println("Part 2: {}", best);
    }
} // namespace day7