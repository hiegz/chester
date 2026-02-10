// clang-format off
// NOLINTBEGIN

#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#include <chester/engine/side.hpp>
#include <chester/engine/piece_type.hpp>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

namespace chester::engine {

class piece {
  public:
    std::int8_t raw;

    constexpr piece() = default;
    template <typename T>
    constexpr explicit piece(T raw) : raw(static_cast<std::uint8_t>(raw)) {}
    constexpr operator std::int8_t() const { return raw; }
    constexpr piece(class side side, class piece_type type)
        : raw(6 * side + type)
    {
#ifdef DEBUG
        if (side.invalid()) {
            throw new std::runtime_error("invalid side");
        }

        if (type.invalid()) {
            throw new std::runtime_error("invalid piece type");
        }
#endif // DEBUG
    }

    [[nodiscard]]
    constexpr auto valid() const -> bool;

    [[nodiscard]]
    constexpr auto invalid() const -> bool;

    [[nodiscard]]
    constexpr auto side() const -> side {
        return (class side)(raw / 6);
    }

    [[nodiscard]]
    constexpr auto type() const -> piece_type {
        return (class piece_type)(raw % 6);
    }

    static const piece white_king;
    static const piece white_queen;
    static const piece white_rook;
    static const piece white_knight;
    static const piece white_bishop;
    static const piece white_pawn;
    static const piece black_king;
    static const piece black_queen;
    static const piece black_rook;
    static const piece black_knight;
    static const piece black_bishop;
    static const piece black_pawn;

    static const piece none;
    static const piece low;
    static const piece high;
};

constexpr piece piece::white_king   = piece(side::white, piece_type::king);
constexpr piece piece::white_queen  = piece(side::white, piece_type::queen);
constexpr piece piece::white_rook   = piece(side::white, piece_type::rook);
constexpr piece piece::white_knight = piece(side::white, piece_type::knight);
constexpr piece piece::white_bishop = piece(side::white, piece_type::bishop);
constexpr piece piece::white_pawn   = piece(side::white, piece_type::pawn);
constexpr piece piece::black_king   = piece(side::black, piece_type::king);
constexpr piece piece::black_queen  = piece(side::black, piece_type::queen);
constexpr piece piece::black_rook   = piece(side::black, piece_type::rook);
constexpr piece piece::black_knight = piece(side::black, piece_type::knight);
constexpr piece piece::black_bishop = piece(side::black, piece_type::bishop);
constexpr piece piece::black_pawn   = piece(side::black, piece_type::pawn);
constexpr piece piece::none         = piece(-1);
constexpr piece piece::low          = piece(-1);
constexpr piece piece::high         = piece(12);

static constexpr std::array<piece, 12> pieces =
    {piece::white_king,
     piece::white_queen,
     piece::white_rook,
     piece::white_knight,
     piece::white_bishop,
     piece::white_pawn,
     piece::black_king,
     piece::black_queen,
     piece::black_rook,
     piece::black_knight,
     piece::black_bishop,
     piece::black_pawn};

constexpr auto piece::valid() const -> bool {
    return raw > piece::low && raw < piece::high;
}

constexpr auto piece::invalid() const -> bool {
    return not valid();
}

auto operator<<(std::ostream &os, piece piece) -> std::ostream &;

}

namespace std {
auto to_string(chester::engine::piece piece) -> std::string;
}

// NOLINTEND
