#include <string>
#include <tuple>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/position.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::engine::piece;
using chester::engine::position;
using chester::engine::side;
using chester::engine::square;

// clang-format off

TEST_CASE("chester::engine::position string representation",
          "[engine][position][fmt]") {
    position    position;
    std::string expected;

    std::tie(position, expected) =
        GENERATE(table<class position, std::string>({
            std::make_tuple(
                position::traditional(),
                "board:\n"
                "r n b q k b n r\n"
                "p p p p p p p p\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                ". . . . . . . .\n"
                "P P P P P P P P\n"
                "R N B Q K B N R\n"
                "turn: white\n"
                "castling: white kingside, white queenside, black kingside, black queenside\n"
                "en passant: none\n"
                "half moves: 0\n"
                "full moves: 1"
             ),

            ([]() -> auto {
                 auto position = position::traditional();

                 position.turn = side::black;

                 return std::make_tuple(
                     position,
                    "board:\n"
                    "r n b q k b n r\n"
                    "p p p p p p p p\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    "P P P P P P P P\n"
                    "R N B Q K B N R\n"
                    "turn: black\n"
                    "castling: white kingside, white queenside, black kingside, black queenside\n"
                    "en passant: none\n"
                    "half moves: 0\n"
                    "full moves: 1"
                 );
            })(),

            ([]() -> auto {
                 auto position = position::traditional();

                 position.board[square::b7] = piece::none;
                 position.board[square::b5] = piece::black_pawn;
                 position.enpassant = square::b6;

                 return std::make_tuple(
                     position,
                    "board:\n"
                    "r n b q k b n r\n"
                    "p . p p p p p p\n"
                    ". . . . . . . .\n"
                    ". p . . . . . .\n"
                    ". . . . . . . .\n"
                    ". . . . . . . .\n"
                    "P P P P P P P P\n"
                    "R N B Q K B N R\n"
                    "turn: white\n"
                    "castling: white kingside, white queenside, black kingside, black queenside\n"
                    "en passant: b6\n"
                    "half moves: 0\n"
                    "full moves: 1"
                 );
            })(),
        }));

    const auto found = std::to_string(position);

    INFO("expected " << expected);
    INFO("");
    INFO("found " << found);

    REQUIRE((found == expected));
}
