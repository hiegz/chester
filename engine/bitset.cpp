#include <ostream>
#include <sstream>
#include <string>

#include <chester/bitset.hpp>
#include <chester/file.hpp>
#include <chester/square.hpp>

// clang-format off

auto chester::operator<<(std::ostream &os, bitset bitset) -> std::ostream & {
    const auto mirrored = bitset.mirror();
    square sq = square::h8;

    while (true) {
        const auto bit = (mirrored & sq) != bitset::empty();

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

auto std::to_string(chester::bitset bitset) -> std::string {
    std::ostringstream ss;
    ss << bitset;
    return ss.str();
}
