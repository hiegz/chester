#include <string>
#include <tuple>

#include <chester/engine/board.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::board;
using chester::engine::piece;
using chester::engine::side;
using chester::engine::square;

// clang-format off

TEST_CASE("chester::engine::board << operator overload for std::ostream",
          "[engine][board][fmt]") {
    board       board;
    std::string expected;

    std::tie(board, expected) =
        GENERATE(table<class board, std::string>({
            std::make_tuple(
                board::empty(),
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
                auto board = board::empty();

                board.get(side::white, piece::king) |= square::e1;
                board.get(side::black, piece::king) |= square::e8;

                return std::make_tuple(
                    board,
                    ". . . . K . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . k . . ."
                );
            })(),

            ([]() -> auto {
                auto board = board::empty();

                board.get(side::white, piece::queen) |= square::d1;
                board.get(side::black, piece::queen) |= square::d8;

                return std::make_tuple(
                    board,
                    ". . . Q . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . q . . . ."
                );
            })(),

            ([]() -> auto {
                auto board = board::empty();

                board.get(side::white, piece::rook) |= square::f7;
                board.get(side::black, piece::pawn) |= square::a1;
                board.get(side::black, piece::bishop) |= square::b5;

                return std::make_tuple(
                    board,
                    ". . . . . . . .\n"
                    ". . . . . r . .\n"
                    ". . . . . . . .\n"
                    ". B . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    "P . . . . . . ."
                );
            })(),

            ([]() -> auto {
                auto board = board::empty();

                board.get(side::white, piece::pawn) |= square::e4;
                board.get(side::white, piece::knight) |= square::b1;
                board.get(side::black, piece::rook) |= square::c6;

                return std::make_tuple(
                    board,
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . R . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . p . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". n . . . . . ."
                );
            })(),
        }));

    const auto found    = std::to_string(board);

    INFO("expected:\n" << expected);
    INFO("");
    INFO("found:\n" << found);

    REQUIRE((found == expected));
}
