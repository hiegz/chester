#pragma once

#include <string>
#include <string_view>
#include <utility>

namespace chester::engine {

class fen : public std::string {
  public:
    constexpr explicit fen(std::string string)
        : std::string(std::move(string)) {}
};

class fen_view : public std::string_view {
  public:
    constexpr explicit fen_view(std::string_view view)
        : std::string_view(view) {}
};

} // namespace chester::engine
