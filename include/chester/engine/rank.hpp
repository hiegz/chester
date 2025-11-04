// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <stdexcept>

namespace chester::engine {

class rank {
  public:
    enum value : std::uint8_t {
        one   = 0,
        two   = 1,
        three = 2,
        four  = 3,
        five  = 4,
        six   = 5,
        seven = 6,
        eight = 7,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr rank(rank::value value) : value(value) {}
    constexpr auto operator==(rank other) const { return value == other.value; }
    constexpr auto operator!=(rank other) const { return value != other.value; }

    enum rank::value value;
};

}

template <>
struct std::formatter<enum chester::engine::rank::value> {
    // cppcheck-suppress[unusedFunction,unmatchedSuppression]
    static constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    static auto format(const enum chester::engine::rank::value &rank, std::format_context &ctx) {
        switch (rank) {
            case chester::engine::rank::one:   return std::format_to(ctx.out(), "1");
            case chester::engine::rank::two:   return std::format_to(ctx.out(), "2");
            case chester::engine::rank::three: return std::format_to(ctx.out(), "3");
            case chester::engine::rank::four:  return std::format_to(ctx.out(), "4");
            case chester::engine::rank::five:  return std::format_to(ctx.out(), "5");
            case chester::engine::rank::six:   return std::format_to(ctx.out(), "6");
            case chester::engine::rank::seven: return std::format_to(ctx.out(), "7");
            case chester::engine::rank::eight: return std::format_to(ctx.out(), "8");
        }

        throw std::runtime_error("unknown rank");
    }
};

template <>
struct std::formatter<chester::engine::rank> : std::formatter<enum chester::engine::rank::value> {
    static auto format(const chester::engine::rank &rank, std::format_context &ctx) {
        return std::format_to(ctx.out(), "{}", rank.value);
    }
};

auto operator<<(std::ostream &os, enum chester::engine::rank::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::rank        const &value) -> std::ostream &;

// NOLINTEND
