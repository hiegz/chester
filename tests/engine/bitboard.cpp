#include <string>
#include <tuple>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::bitboard;
using chester::engine::piece;
using chester::engine::side;
using chester::engine::square;

// clang-format off

TEST_CASE("std::to_string(chester::engine::bitboard)",
          "[engine][board][fmt]") {
    bitboard    board;
    std::string expected;

    std::tie(board, expected) =
        GENERATE(table<class bitboard, std::string>({
            std::make_tuple(
                bitboard::empty(),
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . ."
            ),

            ([]() -> auto {
                auto board = bitboard::empty();

                board[side::white + piece::king] |= square::e1;
                board[side::black + piece::king] |= square::e8;

                return std::make_tuple(
                    board,
                    ". . . . k . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . K . . ."
                );
            })(),

            ([]() -> auto {
                auto board = bitboard::empty();

                board[side::white + piece::queen] |= square::d1;
                board[side::black + piece::queen] |= square::d8;

                return std::make_tuple(
                    board,
                    ". . . q . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . Q . . . ."
                );
            })(),

            ([]() -> auto {
                auto board = bitboard::empty();

                board[side::white + piece::rook]   |= square::f7;
                board[side::black + piece::pawn]   |= square::a1;
                board[side::black + piece::bishop] |= square::b5;

                return std::make_tuple(
                    board,
                    ". . . . . . . .\n"
                    ". . . . . R . .\n"
                    ". . . . . . . .\n"
                    ". b . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    "p . . . . . . ."
                );
            })(),

            ([]() -> auto {
                auto board = bitboard::empty();

                board[side::white + piece::pawn]   |= square::e4;
                board[side::white + piece::knight] |= square::b1;
                board[side::black + piece::rook]   |= square::c6;

                return std::make_tuple(
                    board,
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . r . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . P . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". N . . . . . ."
                );
            })(),
        }));

    const auto found    = std::to_string(board);

    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found);

    REQUIRE((found == expected));
}
