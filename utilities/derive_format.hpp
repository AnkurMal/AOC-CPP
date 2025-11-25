#include "boost/pfr/core_name.hpp"
#include <format>

#define DERIVE_FORMAT(T)                                                       \
    template <>                                                                \
    struct std::formatter<T> {                                                 \
        constexpr auto parse(std::format_parse_context &ctx) {                 \
            return ctx.begin();                                                \
        }                                                                      \
        auto format(const T &p, auto &ctx) const {                             \
            auto out = ctx.out();                                              \
            out = std::format_to(out, #T " {{");                               \
            bool first = true;                                                 \
            boost::pfr::for_each_field_with_name(                              \
                p, [&](std::string_view name, const auto &value) {             \
                    if (!first) out = std::format_to(out, ", ");               \
                    first = false;                                             \
                    out = std::format_to(out, "{}: {}", name, value);          \
                });                                                            \
            out = std::format_to(out, "}}");                                   \
            return out;                                                        \
        }                                                                      \
    };