#include <chester/engine/move.hpp>
#include <chester/engine/move_list.hpp>

#include <cstddef>

#ifdef DEBUG
#include <stdexcept>
#endif // DEBUG

using chester::engine::move;

// clang-format off

namespace {

constexpr auto parent(size_t index) -> size_t {
    return index / 2;
}

constexpr auto left(size_t index) -> size_t {
    return (2 * index) + 1;
}

} // namespace

void chester::engine::move_list::push(move move, size_t priority) {
#ifdef DEBUG
    if (item_count == MAX_SIZE) {
        throw std::runtime_error("unreachable");
    }
#endif // DEBUG

    class move temp_move;
    size_t     temp_weight;
    size_t     child;
    size_t     parent;

    moves[item_count] = move;
    weights[item_count] = priority;
    child = item_count;
    item_count += 1;

    while (child != 0) {
        parent = ::parent(child);

        if (weights[child] < weights[parent]) {
            break;
        }

        temp_move       = moves[child];
        moves[child]    = moves[parent];
        moves[parent]   = move;

        temp_weight     = weights[child];
        weights[child]  = weights[parent];
        weights[parent] = temp_weight;

        child = parent;
    }
}

auto chester::engine::move_list::pop() -> move {
#ifdef DEBUG
    if (item_count == 0) {
        throw std::runtime_error("unreachable");
    }
#endif // DEBUG

    class move ret = moves[0];
    class move temp_move;
    size_t     temp_weight;
    size_t     child;
    size_t     parent;

    item_count -= 1;
    moves[0] = moves[item_count];
    weights[0] = weights[item_count];

    parent = 0;

    // here, |child| is always the left child.
    // If there’s no left child, we can safely assume there's no right child either,
    // because the tree is left-complete (levels are filled top-down, and the last
    // level is populated strictly from left to right with no gaps).
    while ((child = ::left(parent)) < item_count) {
        if (child + 1 < item_count && weights[child] < weights[child + 1]) {
            child += 1; // |child| is the right child now.
        }

        if (weights[parent] > weights[child]) {
            break;
        }

        temp_move       = moves[child];
        moves[child]    = moves[parent];
        moves[parent]   = temp_move;

        temp_weight     = weights[child];
        weights[child]  = weights[parent];
        weights[parent] = temp_weight;

        parent = child;
    }

    return ret;
}
