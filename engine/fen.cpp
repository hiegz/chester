#include <array>
#include <cstddef>
#include <exception>
#include <expected>
#include <iterator>
#include <string>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/board.hpp>
#include <chester/engine/castling.hpp>
#include <chester/engine/fen.hpp>
#include <chester/engine/file.hpp>
#include <chester/engine/piece.hpp>
#include <chester/engine/position.hpp>
#include <chester/engine/rank.hpp>
#include <chester/engine/side.hpp>
#include <chester/engine/square.hpp>

// clang-format off

auto chester::engine::fen_parser::board()
    -> std::expected<class board, std::string> {
    auto board = board::empty();
    file f = file::a;
    rank r = rank::eight;

    skip_whitespace();

    if (it == end) {
        return std::unexpected("invalid FEN");
    }

    while (true) {
        if (it == end) {
            return std::unexpected("invalid FEN");
        }

        const char ch = *it;
        it = std::next(it);

        switch (ch) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                f += (ch - '0');
                continue;

            case ' ':
                if (f != file::high) {
                    return std::unexpected("invalid FEN");
                }
                break;

            case '/':
                if (f != file::high) {
                    return std::unexpected("invalid FEN");
                }
                f = file::a;
                r -= 1;
                continue;

            case 'K':
                board[side::white + piece::king] |= square(f, r);
                f += 1;
                continue;

            case 'Q':
                board[side::white + piece::queen] |= square(f, r);
                f += 1;
                continue;

            case 'R':
                board[side::white + piece::rook] |= square(f, r);
                f += 1;
                continue;

            case 'B':
                board[side::white + piece::bishop] |= square(f, r);
                f += 1;
                continue;

            case 'N':
                board[side::white + piece::knight] |= square(f, r);
                f += 1;
                continue;

            case 'P':
                board[side::white + piece::pawn] |= square(f, r);
                f += 1;
                continue;

            case 'k':
                board[side::black + piece::king] |= square(f, r);
                f += 1;
                continue;

            case 'q':
                board[side::black + piece::queen] |= square(f, r);
                f += 1;
                continue;

            case 'r':
                board[side::black + piece::rook] |= square(f, r);
                f += 1;
                continue;

            case 'b':
                board[side::black + piece::bishop] |= square(f, r);
                f += 1;
                continue;

            case 'n':
                board[side::black + piece::knight] |= square(f, r);
                f += 1;
                continue;

            case 'p':
                board[side::black + piece::pawn] |= square(f, r);
                f += 1;
                continue;

            default:
                return std::unexpected("invalid FEN");
        }

        break;
    }

    return board;
}

auto chester::engine::fen_parser::turn() -> std::expected<side, std::string> {
    skip_whitespace();

    if (it == end) {
        return std::unexpected("invalid FEN");
    }

    const char ch = *it;
    it = std::next(it);

    switch (ch) {
        case 'w':
            return side::white;

        case 'b':
            return side::black;

        default:
            return std::unexpected("invalid FEN");
    }
}

auto chester::engine::fen_parser::castling() -> std::expected<class castling, std::string> {
    skip_whitespace();

    auto castling = castling::none();

    while (true) {
        if (it == end) {
            return std::unexpected("invalid FEN");
        }

        const char ch = *it;
        it = std::next(it);

        switch (ch) {
            case 'K':
                castling |= (side::white + piece::king);
                continue;

            case 'Q':
                castling |= (side::white + piece::queen);
                continue;

            case 'k':
                castling |= (side::black + piece::king);
                continue;

            case 'q':
                castling |= (side::black + piece::queen);
                continue;

            case '-':
            case ' ':
                break;

            default:
                return std::unexpected("invalid FEN");
        }

        break;
    }

    return castling;
}

auto chester::engine::fen_parser::enpassant() -> std::expected<bitboard, std::string> {
    std::array<char, 2> ch;
    file f;
    rank r;

    skip_whitespace();

    if (it == end) {
        return std::unexpected("invalid FEN");
    }

    ch[0] = *it;
    it    = std::next(it);

    if (ch[0] == '-') {
        return bitboard::empty();
    }

    if (it == end) {
        return std::unexpected("invalid FEN");
    }

    ch[1] = *it;
    it = std::next(it);

    f = (enum file::value)(ch[0] - 'a');
    r = (enum rank::value)(ch[1] - '1');

    if (f < file::low or f > file::high or r < rank::low or r > rank::high) {
        return std::unexpected("invalid FEN");
    }

    return square(f, r);
}

auto chester::engine::fen_parser::moves() -> std::expected<std::size_t, std::string> {
    std::string str;

    skip_whitespace();

    while (true) {
        if (it == end) {
            break;
        }
        const char ch = *it;
        if (ch == ' ') {
            break;
        }
        it = std::next(it);
        str += ch;
    }

    try {
        return std::stoul(str);
    } catch (std::exception const &e) {
        return std::unexpected("invalid FEN");
    }
}

auto chester::engine::fen_parser::position() -> std::expected<class position, std::string> {
    const auto lo_board = this->board();
    if (not lo_board) {
        return std::unexpected(lo_board.error());
    }

    const auto lo_turn = this->turn();
    if (not lo_turn) {
        return std::unexpected(lo_turn.error());
    }

    const auto lo_castling = this->castling();
    if (not lo_castling) {
        return std::unexpected(lo_castling.error());
    }

    const auto lo_enpassant = this->enpassant();
    if (not lo_enpassant) {
        return std::unexpected(lo_enpassant.error());
    }

    const auto lo_half_moves = this->moves();
    if (not lo_half_moves) {
        return std::unexpected(lo_half_moves.error());
    }

    const auto lo_full_moves = this->moves();
    if (not lo_full_moves) {
        return std::unexpected(lo_full_moves.error());
    }

    if (it != end) {
        return std::unexpected("invalid FEN");
    }

    return chester::engine::position(*lo_board, *lo_turn, *lo_castling, *lo_enpassant, *lo_half_moves, *lo_full_moves);
}

auto chester::engine::fen_parser::skip_whitespace() -> void {
    while (it != end and *it == ' ') {
        it = std::next(it);
    }
}
