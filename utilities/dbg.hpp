#pragma once

#include <source_location>

#define dbg(expr)                                                              \
    ([&](auto &&val) {                                                         \
        std::println("[{}:{}:{}] {} = {}",                                     \
                     std::source_location::current().file_name(),              \
                     std::source_location::current().line(),                   \
                     std::source_location::current().column(), #expr, val);    \
        return val;                                                            \
    }(expr))