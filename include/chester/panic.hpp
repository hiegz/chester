// clang-format off

#pragma once

#include <cstdio>
#include <cstdlib>
#include <format>
#include <source_location>
#include <type_traits>

namespace chester {

// stolen from
//
// https://buildingblock.ai/panic

template <class... Args>
struct panic_format {
    template <class T>
    // cppcheck-suppress noExplicitConstructor
    consteval panic_format(const T &s, std::source_location loc = std::source_location::current()) noexcept // NOLINT
        : fmt{s}, loc{loc} {}

    std::format_string<Args...> fmt{};
    std::source_location        loc;
};

template <class... Args>
[[noreturn]] void panic(panic_format<std::type_identity_t<Args>...> fmt, Args &&...args) {
    auto msg =
        std::format(
                "{}:{} panic: {}\n",
                fmt.loc.file_name(),
                fmt.loc.line(),
                std::format(fmt.fmt, std::forward<Args>(args)...));

    std::fputs(msg.c_str(), stderr);
    std::abort();
}

}
