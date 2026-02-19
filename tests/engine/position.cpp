#include <string>
#include <tuple>

#include <chester/board.hpp>
#include <chester/piece.hpp>
#include <chester/position.hpp>
#include <chester/side.hpp>
#include <chester/square.hpp>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using chester::piece;
using chester::position;
using chester::side;
using chester::square;

// clang-format off

TEMPLATE_TEST_CASE("chester::position string representation", "[engine][position][fmt]", piece, square) {
    position<TestType> position;
    std::string        expected;

    std::tie(position, expected) =
        GENERATE(table<::position<TestType>, std::string>({
            std::make_tuple(
                ::position<TestType>::traditional(),
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
                 auto position = ::position<TestType>::traditional();

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
        }));

    const auto found = std::to_string(position);

    INFO("expected " << expected);
    INFO("");
    INFO("found " << found);

    REQUIRE((found == expected));
}

TEST_CASE("chester::position<piece> string representation", "[engine][position<piece>][fmt]") {
    auto position = ::position<piece>::traditional();

    position.board[piece::black_pawn] ^= square::b7;
    position.board[piece::black_pawn] |= square::b5;
    position.enpassant                 = square::b6;

    const std::string found = std::to_string(position);
    const std::string expected =
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
        "castling: white kingside, white queenside, black kingside, black "
        "queenside\n"
        "en passant: b6\n"
        "half moves: 0\n"
        "full moves: 1";

    INFO("expected " << expected);
    INFO("");
    INFO("found " << found);

    REQUIRE((found == expected));
}

TEST_CASE("chester::position<square> string representation", "[engine][position<square>][fmt]") {
    auto position = ::position<square>::traditional();

    position.board[square::b7] = piece::none;
    position.board[square::b5] = piece::black_pawn;
    position.enpassant         = square::b6;

    const std::string found = std::to_string(position);
    const std::string expected =
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
        "castling: white kingside, white queenside, black kingside, black "
        "queenside\n"
        "en passant: b6\n"
        "half moves: 0\n"
        "full moves: 1";

    INFO("expected " << expected);
    INFO("");
    INFO("found " << found);

    REQUIRE((found == expected));
}
