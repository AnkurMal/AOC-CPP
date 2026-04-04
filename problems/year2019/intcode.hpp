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
                 return std::stoll(std::string{x.begin(), x.end()});
             })
           | std::ranges::to<std::vector>();
}

auto get_value(const vector<long long> &vec, long long mode, long long pos,
               long long relative_base) {
    if (mode == 0) return vec[vec[pos]];
    else if (mode == 1) return vec[pos];
    else if (mode == 2) return vec[vec[pos] + relative_base];
    return 0LL;
}

long long get_address(vector<long long> &vec, long long mode, long long pos,
                      long long base) {
    if (mode == 0) return vec[pos];
    else if (mode == 2) return vec[pos] + base;
    return 0LL;
}

auto intcode(vector<long long> &vec, int input = 0) {
    auto original_size = vec.size();
    vec.resize(1000000, 0);
    int opcode{};
    long long base{}, output{}, i{};

    while ((opcode = vec[i] % 100) != 99) {
        const auto m1{vec[i] / 100 % 10};
        const auto m2{vec[i] / 1000 % 10};
        const auto m3{vec[i] / 10000};

        const auto v1{get_value(vec, m1, i + 1, base)};
        const auto v2{get_value(vec, m2, i + 2, base)};

        switch (opcode) {
        case 1: {
            long long a3 = get_address(vec, m3, i + 3, base);
            vec[a3] = v1 + v2;
            i += 4;
            break;
        }

        case 2: {
            long long a3 = get_address(vec, m3, i + 3, base);
            vec[a3] = v1 * v2;
            i += 4;
            break;
        }

        case 3: {
            long long a1 = get_address(vec, m1, i + 1, base);
            vec[a1] = input;
            i += 2;
            break;
        }

        case 4: {
            output = v1;
            i += 2;
            break;
        }

        case 5: {
            if (v1 != 0) i = v2;
            else i += 3;
            break;
        }

        case 6: {
            if (v1 == 0) i = v2;
            else i += 3;
            break;
        }

        case 7: {
            long long a3 = get_address(vec, m3, i + 3, base);
            vec[a3] = v1 < v2;
            i += 4;
            break;
        }

        case 8: {
            long long a3 = get_address(vec, m3, i + 3, base);
            vec[a3] = v1 == v2;
            i += 4;
            break;
        }

        case 9: {
            base += v1;
            i += 2;
            break;
        }

        default:
            i++;
        }
    }

    vec.resize(original_size);
    return output;
}
