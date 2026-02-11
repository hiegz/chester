#include <chester/engine/move_type.hpp>

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

using chester::engine::move_type;

// clang-format off

auto chester::engine::operator<<(std::ostream &os, move_type type) -> std::ostream & {
    switch (type) {
        case move_type::normal:    return os << "normal";
        case move_type::promotion: return os << "promotion";
        case move_type::enpassant: return os << "en passant";
        case move_type::castling:  return os << "castling";

        default:
           throw std::runtime_error("unreachable");
    }
}

auto std::to_string(chester::engine::move_type type) -> std::string {
    std::ostringstream ss;
    ss << type;
    return ss.str();
}
