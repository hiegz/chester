#pragma once

#include <array>
#include <cstddef>

#include <chester/move.hpp>

// clang-format off

namespace chester {

class move_list {
  private:
    /**
     * The maximum number of legal moves in a chess position. The known
     * record is 218 moves, but computers are better at handling the set
     * number.
     */
    constexpr static size_t MAX_SIZE = 256;

  public:
    void push(move move, size_t priority);
    auto pop() -> move;

    [[nodiscard]]
    auto size() const -> size_t {
        return item_count;
    }

  private:
    std::array<move,   MAX_SIZE> moves;
    std::array<size_t, MAX_SIZE> weights;
    std::size_t item_count;

};

} // namespace chester::engine
