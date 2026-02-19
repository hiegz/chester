#include <string>
#include <tuple>

#include <chester/board.hpp>
#include <chester/piece.hpp>
#include <chester/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::board;
using chester::piece;
using chester::square;

// clang-format off

TEST_CASE("std::to_string(chester::board<chester::piece>)",
          "[engine][board<piece>][fmt]") {
    board<piece> board;
    std::string  expected;

    std::tie(board, expected) =
        GENERATE(table<::board<piece>, std::string>({
            std::make_tuple(
                ::board<piece>::empty(),
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
                auto board = ::board<piece>::empty();

                board[piece::white_king] |= square::e1;
                board[piece::black_king] |= square::e8;

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
                auto board = ::board<piece>::empty();

                board[piece::white_queen] |= square::d1;
                board[piece::black_queen] |= square::d8;

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
                auto board = ::board<piece>::empty();

                board[piece::white_rook]   |= square::f7;
                board[piece::black_pawn]   |= square::a1;
                board[piece::black_bishop] |= square::b5;

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
                auto board = ::board<piece>::empty();

                board[piece::white_pawn]   |= square::e4;
                board[piece::white_knight] |= square::b1;
                board[piece::black_rook]   |= square::c6;

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

    const auto found = std::to_string(board);

    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found);

    REQUIRE((found == expected));
}

TEST_CASE("std::to_string(chester::board<chester::square>)",
          "[engine][board<square>][fmt]") {
    board<square> board;
    std::string  expected;

    std::tie(board, expected) =
        GENERATE(table<::board<square>, std::string>({
            std::make_tuple(
                ::board<square>::empty(),
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
                auto board = ::board<square>::empty();

                board[square::e1] = piece::white_king;
                board[square::e8] = piece::black_king;

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
                auto board = ::board<square>::empty();

                board[square::d1] = piece::white_queen;
                board[square::d8] = piece::black_queen;

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
                auto board = ::board<square>::empty();

                board[square::f7] = piece::white_rook;
                board[square::a1] = piece::black_pawn;
                board[square::b5] = piece::black_bishop;

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
                auto board = ::board<square>::empty();

                board[square::e4] = piece::white_pawn;
                board[square::b1] = piece::white_knight;
                board[square::c6] = piece::black_rook;

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

    const auto found = std::to_string(board);

    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found);

    REQUIRE((found == expected));
}
