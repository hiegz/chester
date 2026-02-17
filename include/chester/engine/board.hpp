#pragma once

#include <chester/engine/bitset.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/square.hpp>

#include <array>
#include <ostream>
#include <string>

// clang-format off

namespace chester::engine {

template <typename Index>
class board;

template<>
class board<piece>;

template <>
class board<square>;

/** Piece-oriented board representation. */
template <>
class board<piece> {
  public:
    std::array<bitset, 12> pieces;

    board(board<square> const &board);
    board() = default;
    static auto empty() -> board;
    static auto traditional() -> board;

    constexpr auto operator==(board const &other) const -> bool = default;
    constexpr auto operator!=(board const &other) const -> bool = default;
    constexpr auto operator[](piece        piece) const -> bitset const & { return pieces[piece.raw]; }
    constexpr auto operator[](piece        piece)       -> bitset &       { return pieces[piece.raw]; }
};

/** Square-oriented board representation. */
template <>
class board<square> {
  public:
    std::array<piece, 64> squares;

    board(board<piece> const &board);
    board() = default;
    static auto empty() -> board;
    static auto traditional() -> board;

    constexpr auto operator==(board  const &other) const -> bool = default;
    constexpr auto operator!=(board  const &other) const -> bool = default;
    constexpr auto operator[](square       square) const -> piece const & { return squares[square.raw]; }
    constexpr auto operator[](square       square)       -> piece &       { return squares[square.raw]; }
};

auto operator<<(std::ostream &os, board<piece> const &board)
    -> std::ostream &;

auto operator<<(std::ostream &os, board<square> const &board)
    -> std::ostream &;

} // namespace chester::engine

namespace std {
auto to_string(chester::engine::board<chester::engine::piece>  const &board) -> std::string;
auto to_string(chester::engine::board<chester::engine::square> const &board) -> std::string;
}
