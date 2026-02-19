#pragma once

#include <chester/bitset.hpp>
#include <chester/piece.hpp>
#include <chester/side.hpp>
#include <chester/square.hpp>

#include <array>
#include <ostream>
#include <string>

// clang-format off

namespace chester {

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
    static auto empty()       -> board<piece>;
    static auto traditional() -> board<piece>;

    constexpr auto operator==(board<piece> const &other) const -> bool = default;
    constexpr auto operator!=(board<piece> const &other) const -> bool = default;
    constexpr auto operator[](piece               piece) const -> bitset const & { return pieces[piece.raw]; }
    constexpr auto operator[](piece               piece)       -> bitset       & { return pieces[piece.raw]; }

    [[nodiscard]]
    auto occupancy() const -> bitset;

    [[nodiscard]]
    auto select(side side) const -> bitset;
};

/** Square-oriented board representation. */
template <>
class board<square> {
  public:
    std::array<piece, 64> squares;

    board(board<piece> const &board);
    board() = default;
    static auto empty()       -> board<square>;
    static auto traditional() -> board<square>;

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
auto to_string(chester::board<chester::piece>  const &board) -> std::string;
auto to_string(chester::board<chester::square> const &board) -> std::string;
}
