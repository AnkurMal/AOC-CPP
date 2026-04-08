#pragma once

#include <algorithm>
#include <cctype>
#include <charconv>
#include <string_view>

using namespace std;

#define parse_digit(str, dest)                                                 \
    from_chars(str.data(), str.data() + str.size(), dest)

auto is_digit(string_view string) {
    return ranges::all_of(string, [](auto &&x) { return isdigit(x); });
}