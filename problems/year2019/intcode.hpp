#pragma once

#include <fstream>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

auto get_data(std::ifstream &file) {
    std::string data{std::istreambuf_iterator{file}, {}};
    return data
           | std::views::lazy_split(',')
           | std::views::transform([](auto &&rng) {
                 auto x = rng | std::views::common;
                 return std::stoi(std::string{x.begin(), x.end()});
             })
           | std::ranges::to<std::vector>();
}

auto get_value(const vector<int> &vec, const int mode, const int pos) {
    auto size{vec.size()};

    if (pos >= size) return 0;
    else if (mode == 0) {
        return (vec[pos] < size) ? vec[vec[pos]] : 0;
    } else return vec[pos];
}

auto intcode(vector<int> &vec, int input = 0) {
    int i{}, opcode, output{};

    while ((opcode = vec[i] % 100) != 99) {
        const auto m1{vec[i] / 100 % 10};
        const auto m2{vec[i] / 1000 % 10};

        const auto v1{get_value(vec, m1, i + 1)};
        const auto v2{get_value(vec, m2, i + 2)};

        switch (opcode) {
        case 1:
            vec[vec[i + 3]] = v1 + v2;
            i += 4;
            break;

        case 2:
            vec[vec[i + 3]] = v1 * v2;
            i += 4;
            break;

        case 3:
            vec[vec[i + 1]] = input;
            i += 2;
            break;

        case 4:
            output = v1;
            i += 2;
            break;

        case 5:
            if (v1 != 0) i = v2;
            else i += 3;
            break;

        case 6:
            if (v1 == 0) i = v2;
            else i += 3;
            break;

        case 7:
            vec[vec[i + 3]] = v1 < v2;
            i += 4;
            break;

        case 8:
            vec[vec[i + 3]] = v1 == v2;
            i += 4;
            break;

        default:
            i++;
        }
    }

    return output;
}
