#pragma once

#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <utility>

// clang-format off

namespace chester::engine {

class bitboard;
class board;
class position;
enum class side : std::uint8_t;
class castling;

class fen : public std::string {
  public:
    constexpr fen(std::string string)
        : std::string(std::move(string)) {}
};

class fen_view : public std::string_view {
  public:
    constexpr fen_view(std::string_view view)
        : std::string_view(view) {}
};

class fen_parser {
  public:
    constexpr fen_parser(fen_view view)
        : it(view.begin()), end(view.end()) {}

    constexpr fen_parser(std::string_view view)
        : it(view.begin()), end(view.end()) {}

    auto board() -> std::expected<board, std::string>;
    auto turn() -> std::expected<side, std::string>;
    auto castling() -> std::expected<castling, std::string>;
    auto enpassant() -> std::expected<bitboard, std::string>;
    auto moves() -> std::expected<std::size_t, std::string>;
    auto position() -> std::expected<position, std::string>;

    fen_view::iterator it;
    fen_view::iterator end;

  private:
    auto skip_whitespace() -> void;
};

} // namespace chester::engine
