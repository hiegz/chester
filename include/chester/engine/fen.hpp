#pragma once

#include <string>
#include <utility>

namespace chester::engine {

/**
 * Forsyth-Edwards Notation
 */
class fen {
  public:
    constexpr explicit fen(std::string string) : string(std::move(string)) {}
    std::string string;
};

} // namespace chester::engine
