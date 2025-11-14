// clang-format off

#include <ostream>
#include <string>
#include <sstream>

#include <chester/engine/bitset.hpp>
#include <chester/engine/square.hpp>
#include <chester/engine/file.hpp>

auto chester::engine::operator<<(std::ostream &os, chester::engine::bitset bitset)
    -> std::ostream & {
    const auto   mirrored = bitset.mirror();
          square sq       = square::h8;

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

auto std::to_string(chester::engine::bitset bitset) -> std::string {
    std::ostringstream ss;
    ss << bitset;
    return ss.str();
}
