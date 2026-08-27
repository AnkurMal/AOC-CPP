#include <meta>
#include <format>
#include <print>
#include <string>

#define DERIVE_FORMAT(T)                                                       \
    namespace std {                                                            \
        template <>                                                            \
        struct formatter<T> {                                                  \
            constexpr auto parse(std::format_parse_context &ctx) {             \
                return ctx.begin();                                            \
            }                                                                  \
            auto format(const T &p, auto &ctx) const {                         \
                auto out = ctx.out();                                          \
                out = std::format_to(out, #T " {{");                           \
                bool first = true;                                             \
                template for (constexpr auto mem : std::define_static_array(   \
                                  std::meta::nonstatic_data_members_of(        \
                                      ^^T, std::meta::access_context::         \
                                               current()))) {                  \
                    if (!first) out = std::format_to(out, ", ");               \
                    first = false;                                             \
                    out = std::format_to(out, "{}: {}",                        \
                                         std::meta::identifier_of(mem),        \
                                         p.[:mem:]);                           \
                }                                                              \
                out = std::format_to(out, "}}");                               \
                return out;                                                    \
            }                                                                  \
        };                                                                     \
    }
