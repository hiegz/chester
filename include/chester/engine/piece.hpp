// clang-format off
// NOLINTBEGIN

#pragma once

#include <cstdint>
#include <format>
#include <ostream>
#include <stdexcept>

namespace chester::engine {

class piece {
  public:
    enum value : std::uint8_t {
        king,
        queen,
        rook,
        bishop,
        knight,
        pawn,
    };

    // cppcheck-suppress noExplicitConstructor
    constexpr piece(piece::value value) : value(value) {}
    constexpr auto operator==(piece other) const { return value == other.value; }
    constexpr auto operator!=(piece other) const { return value != other.value; }

    enum piece::value value;
};

}

template <>
struct std::formatter<enum chester::engine::piece::value> {
    // cppcheck-suppress[unusedFunction,unmatchedSuppression]
    static constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    static auto format(const enum chester::engine::piece::value &piece, std::format_context &ctx) {
        switch (piece) {
            case chester::engine::piece::king:   return std::format_to(ctx.out(), "king");
            case chester::engine::piece::queen:  return std::format_to(ctx.out(), "queen");
            case chester::engine::piece::rook:   return std::format_to(ctx.out(), "rook");
            case chester::engine::piece::bishop: return std::format_to(ctx.out(), "bishop");
            case chester::engine::piece::knight: return std::format_to(ctx.out(), "knight");
            case chester::engine::piece::pawn:   return std::format_to(ctx.out(), "pawn");
        }

        throw std::runtime_error("unknown piece");
    }
};


template <>
struct std::formatter<chester::engine::piece> : std::formatter<enum chester::engine::piece::value> {
    static auto format(const chester::engine::piece &piece, std::format_context &ctx) {
        return std::format_to(ctx.out(), "{}", piece.value);
    }
};

auto operator<<(std::ostream &os, enum chester::engine::piece::value const &value) -> std::ostream &;
auto operator<<(std::ostream &os,      chester::engine::piece        const &value) -> std::ostream &;

// NOLINTEND
