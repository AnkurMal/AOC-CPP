#pragma once

#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

inline int get_value(const std::vector<int> &vec, int mode, int pos) {
    if (mode == 1) {
        return vec[pos];
    }

    int address = vec[pos];
    if (address < 0 || address >= static_cast<int>(vec.size())) {
        return 0;
    }

    return vec[address];
}

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

inline int run_once(std::vector<int> vec, const std::vector<int> &inputs) {
    int i{}, opcode, output{};
    int ip = 0;

    while ((opcode = vec[i] % 100) != 99) {
        const auto m1{vec[i] / 100 % 10};
        const auto m2{vec[i] / 1000 % 10};

        const auto v1 = get_value(vec, m1, i + 1);
        const auto v2 = get_value(vec, m2, i + 2);

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
            vec[vec[i + 1]] = inputs[ip++];
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

struct Amp {
    std::vector<int> vec;
    int i = 0;
    bool halted = false;
};

inline int run(Amp &a, std::vector<int> &inputs) {
    int opcode;

    while ((opcode = a.vec[a.i] % 100) != 99) {
        int m1 = a.vec[a.i] / 100 % 10;
        int m2 = a.vec[a.i] / 1000 % 10;

        int v1 = get_value(a.vec, m1, a.i + 1);
        int v2 = get_value(a.vec, m2, a.i + 2);

        switch (opcode) {
        case 1:
            a.vec[a.vec[a.i + 3]] = v1 + v2;
            a.i += 4;
            break;

        case 2:
            a.vec[a.vec[a.i + 3]] = v1 * v2;
            a.i += 4;
            break;

        case 3:
            if (inputs.empty()) return -1;
            a.vec[a.vec[a.i + 1]] = inputs.front();
            inputs.erase(inputs.begin());
            a.i += 2;
            break;

        case 4:
            a.i += 2;
            return v1;

        case 5:
            if (v1 != 0) a.i = v2;
            else a.i += 3;
            break;

        case 6:
            if (v1 == 0) a.i = v2;
            else a.i += 3;
            break;

        case 7:
            a.vec[a.vec[a.i + 3]] = v1 < v2;
            a.i += 4;
            break;

        case 8:
            a.vec[a.vec[a.i + 3]] = v1 == v2;
            a.i += 4;
            break;

        default:
            a.i++;
        }
    }

    a.halted = true;
    return -1;
}

namespace day7 {
    inline std::ifstream file{PATH "/data/year2019/day7.txt"};

    inline void part1() {
        auto program = get_data(file);

        std::vector<int> p{0, 1, 2, 3, 4};
        int best = 0;

        do {
            int signal = 0;
            signal = run_once(program, {p[0], signal});
            signal = run_once(program, {p[1], signal});
            signal = run_once(program, {p[2], signal});
            signal = run_once(program, {p[3], signal});
            signal = run_once(program, {p[4], signal});
            if (signal > best) best = signal;
        } while (std::next_permutation(p.begin(), p.end()));

        std::println("Part 1: {}", best);
    }

    inline void part2() {
        auto program = get_data(file);

        std::vector<int> p{5, 6, 7, 8, 9};
        int best = 0;

        do {
            std::vector<Amp> amps(5);
            for (int i = 0; i < 5; i++)
                amps[i].vec = program;

            std::vector<std::vector<int>> inputs(5);
            for (int i = 0; i < 5; i++)
                inputs[i].push_back(p[i]);

            inputs[0].push_back(0);

            int last_output = 0;

            while (!amps[4].halted) {
                for (int i = 0; i < 5; i++) {
                    int out = run(amps[i], inputs[i]);
                    if (out != -1) {
                        inputs[(i + 1) % 5].push_back(out);
                        if (i == 4) last_output = out;
                    }
                }
            }

            if (last_output > best) best = last_output;

        } while (std::next_permutation(p.begin(), p.end()));

        std::println("Part 2: {}", best);
    }
} // namespace day7