#include <expected>
#include <string>
#include <tuple>

#include <chester/engine/board.hpp>
#include <chester/engine/castling.hpp>
#include <chester/engine/fen.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/position.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::board;
using chester::engine::castling;
using chester::engine::fen_parser;
using chester::engine::piece;
using chester::engine::position;
using chester::engine::side;
using chester::engine::square;

// clang-format off

TEMPLATE_TEST_CASE("construct chester::engine::position from FEN", "[engine][position][fen]", piece, square) {
    std::string fen;
    std::expected<position<TestType>, std::string> expected;

    std::tie(fen, expected) =
        GENERATE(table<std::string, std::expected<position<TestType>, std::string>>({
            std::make_tuple(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                position<TestType>::traditional()
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 b - a5 5 15",
                position<TestType>(board<TestType>::empty(), side::black, castling::none, square::a5, 5, 15)
            ),

            std::make_tuple(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "9/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "ppp/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "6/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "6p/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8//8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/7/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/6p/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/PPPPPPPP/ w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/PPPPPPPP/p w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/PPPPPPPP/7 w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/a/8/8/8 w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/p8/8/8 w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/88/8/8/8 w KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 - KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 a KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 KQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 - - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w KQkq",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w KQkq ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w KQkq  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w aQkq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w KQaq - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w b - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - e8",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - e8 ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - e8  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - j 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - j8 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - p9 0 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0 ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 18446744073709551616 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - a 1",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0 1 ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0 1  ",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0 18446744073709551616",
                std::unexpected("invalid FEN")
            ),

            std::make_tuple(
                "8/8/8/8/8/8/8/8 w - - 0 b",
                std::unexpected("invalid FEN")
            ),
        }));


    std::expected<position<TestType>, std::string> found = fen_parser(fen).position<TestType>();

    INFO("expected " << (expected ? std::to_string(*expected) : expected.error()));
    INFO("");
    INFO("found " << (found ? std::to_string(*found) : found.error()));

    REQUIRE((found == expected));
}
