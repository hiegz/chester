#include <chester/engine/castling.hpp>

#include <array>
#include <ostream>
#include <sstream>
#include <string>

using chester::engine::castling;

// clang-format off

auto chester::engine::operator<<(std::ostream &os, castling castling)
    -> std::ostream & {
    static constexpr std::array<std::string, 4> fmt =
        {"white kingside", "white queenside", "black kingside", "black queenside"};

    bool prev = false;
    for (unsigned int i = 0; i < 4; ++i) {
        if ((castling.value & (1UL << i)) != 0) {
            if (prev) {
                os << ", ";
            }
            prev = true;
            os << fmt[i];
        }
    }

    return os;
}

auto std::to_string(castling castling) -> std::string {
    std::ostringstream ss;
    ss << castling;
    return ss.str();
}
