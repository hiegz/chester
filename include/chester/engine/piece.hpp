// clang-format off
// NOLINTBEGIN

#pragma once

#include <array>
#include <ostream>
#include <string>

#include <chester/engine/side.hpp>
#include <chester/engine/piece_type.hpp>

namespace chester::engine {

class piece {
  public:
    constexpr piece() = default;

    constexpr piece(enum side side, enum piece_type type)
        : side(side), type(type) {}

    enum side side;
    enum piece_type type;

    //

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

auto operator<<(std::ostream &os, piece piece) -> std::ostream &;

}

namespace std {
auto to_string(chester::engine::piece piece) -> std::string;
}

// NOLINTEND
