#pragma once

#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <algorithm>
#include <array>
#include <ostream>
#include <string>

namespace chester::engine {

// clang-format off

class bitboard;

class board {
  public:
    board(bitboard const &bitboard);

    constexpr board() = default;

    constexpr static auto empty() -> board {
        board b;
        std::ranges::fill(b.squares, piece::none);
        return b;
    }

    constexpr static auto traditional() -> board {
        using chester::engine::square;

        board board = board::empty();

        board[square::a1] = piece::white_rook;
        board[square::b1] = piece::white_knight;
        board[square::c1] = piece::white_bishop;
        board[square::d1] = piece::white_queen;
        board[square::e1] = piece::white_king;
        board[square::f1] = piece::white_bishop;
        board[square::g1] = piece::white_knight;
        board[square::h1] = piece::white_rook;

        for (auto file : files) {
            board[square(file, rank::two)] = piece::white_pawn;
        }

        board[square::a8] = piece::black_rook;
        board[square::b8] = piece::black_knight;
        board[square::c8] = piece::black_bishop;
        board[square::d8] = piece::black_queen;
        board[square::e8] = piece::black_king;
        board[square::f8] = piece::black_bishop;
        board[square::g8] = piece::black_knight;
        board[square::h8] = piece::black_rook;

        for (auto file : files) {
            board[square(file, rank::seven)] = piece::black_pawn;
        }

        return board;
    }

    constexpr auto operator[](chester::engine::square sq) const -> piece const & {
        return this->squares[sq.raw];
    }

    constexpr auto operator[](chester::engine::square sq) -> piece & {
        return this->squares[sq.raw];
    }

  private:
    /**
     * State of each square on the board.
     *
     * [[ 0]] = a1;
     * [[ 1]] = b1;
     * [[ 2]] = c1;
     *    .
     *    .
     *    .
     * [[ 8]] = a2;
     *    .
     *    .
     *    .
     * [[63]] = h8;
     */
    std::array<piece, 64> squares;
};

auto operator<<(std::ostream &os, chester::engine::board const &board)
    -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::board const &board) -> std::string;
}
