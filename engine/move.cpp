#include <chester/move.hpp>
#include <chester/move_type.hpp>

#include <ostream>
#include <sstream>
#include <string>

using chester::move;

// clang-format off

auto chester::operator<<(std::ostream &os, move move) -> std::ostream & {
    auto origin = move.origin();
    auto destination = move.destination();
    auto type = move.type();

    os << origin << " -> " << destination;

    if (type == move_type::normal) {
        return os;
    }

    os << " ";
    os << "(";
    os << type;

    if (type == move_type::promotion) {
        os << " to " << move.promotion_piece();
    }

    os << ")";

    return os;
}

auto std::to_string(chester::move move) -> std::string {
    std::ostringstream ss;
    ss << move;
    return ss.str();
}
