// clang-format off

#include <ostream>
#include <string>
#include <sstream>

#include <chester/engine/bitboard.hpp>
#include <chester/engine/square.hpp>
#include <chester/engine/file.hpp>

auto chester::engine::operator<<(std::ostream &os, chester::engine::bitboard const &bitboard)
    -> std::ostream & {
    const auto   mirrored = chester::engine::bitboard::mirror(bitboard);
          square sq       = square::h8;

    while (true) {
        const auto bit = (mirrored & sq) != bitboard::empty();

        if (sq != square::h8) {
            os << (sq.file() == file::h ? '\n' : ' ');
        }
        os << ((bit) ? '1' : '.');

        if (sq == square::a1) {
            break;
        }
        sq <<= 1;
    }

    return os;
}

auto std::to_string(chester::engine::bitboard bitboard) -> std::string {
    std::ostringstream ss;
    ss << bitboard;
    return ss.str();
}
