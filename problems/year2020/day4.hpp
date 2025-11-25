#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace day4 {
    using namespace std::literals;
    inline std::ifstream file{PATH "data/year2020/day4.txt"};

    inline void part1() {
        std::string data{std::istreambuf_iterator{file}, {}};
        const std::vector<std::string_view> fields{"byr", "iyr", "eyr", "hgt",
                                                   "hcl", "ecl", "pid"};

        int count{};
        const auto spl1 = data
                          | std::views::lazy_split("\n\n"sv)
                          | std::ranges::to<std::vector<std::string>>();

        for (std::string_view st : spl1) {
            auto spl2 = st
                        | std::views::split('\n')
                        | std::ranges::to<std::vector<std::string>>();
            std::vector<std::string> fin;

            for (std::string_view st1 : spl2) {
                auto spl3 = st1
                            | std::views::split(' ')
                            | std::ranges::to<std::vector<std::string>>();

                for (auto &&st2 : spl3)
                    fin.push_back(st2.substr(0, 3));
            }

            for (std::string_view fiel : fields) {
                if (!std::ranges::contains(fin, fiel)) goto outer;
            }
            count++;

        outer:;
        }

        std::println("Part 1: {}", count);
    }

    inline void part2() {
        std::string data{std::istreambuf_iterator{file}, {}};
        const std::vector<std::string_view> fields{"byr", "iyr", "eyr", "hgt",
                                                   "hcl", "ecl", "pid"};

        int count{};
        const auto spl1 = data
                          | std::views::lazy_split("\n\n"sv)
                          | std::ranges::to<std::vector<std::string>>();

        for (std::string_view st : spl1) {
            auto spl2 = st
                        | std::views::split('\n')
                        | std::ranges::to<std::vector<std::string>>();
            std::vector<std::string> fin;

            for (std::string_view st1 : spl2) {
                auto spl3 = st1
                            | std::views::split(' ')
                            | std::ranges::to<std::vector<std::string>>();

                for (auto &&field : spl3) {
                    auto key = field.substr(0, 3);
                    auto val = field.substr(4);

                    try {
                        if (key == "byr") {
                            const int n = std::stoi(std::string(val));
                            if (n < 1920 || n > 2002) goto outer;
                        } else if (key == "iyr") {
                            const int n = std::stoi(std::string(val));
                            if (n < 2010 || n > 2020) goto outer;
                        } else if (key == "eyr") {
                            const int n = std::stoi(std::string(val));
                            if (n < 2020 || n > 2030) goto outer;
                        } else if (key == "hgt") {
                            if (!(val.ends_with("cm") || val.ends_with("in")))
                                goto outer;
                            const int n = std::stoi(
                                std::string(val.substr(0, val.size() - 2)));
                            if (val.ends_with("cm") && (n < 150 || n > 193))
                                goto outer;
                            if (val.ends_with("in") && (n < 59 || n > 76))
                                goto outer;
                        } else if (key == "hcl") {
                            if (val.size() != 7 || val[0] != '#') goto outer;
                            for (const char c : val.substr(1))
                                if (!(std::isdigit(
                                          static_cast<unsigned char>(c))
                                      || (c >= 'a' && c <= 'f')))
                                    goto outer;
                        } else if (key == "ecl") {
                            static constexpr std::string_view colors[]{
                                "amb", "blu", "brn", "gry",
                                "grn", "hzl", "oth"};
                            if (!std::ranges::contains(colors, val)) goto outer;
                        } else if (key == "pid") {
                            if (val.size()
                                != 9
                                || !std::ranges::all_of(val, [](const char c) {
                                       return c >= '0' && c <= '9';
                                   }))
                                goto outer;
                        }
                    } catch (...) {
                        goto outer;
                    }

                    fin.push_back(std::string(key));
                }
            }

            for (std::string_view fiel : fields) {
                if (!std::ranges::contains(fin, fiel)) goto outer;
            }
            count++;

        outer:;
        }

        std::println("Part 2: {}", count);
    }
} // namespace day4
