// clang-format off

#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#ifdef DEBUG
#include <chester/panic.hpp>
#endif

namespace chester::engine::bitset {

/** Returns an empty bitset */
template <typename T>
auto constexpr empty() -> T;

template <>
auto constexpr empty() -> std::uint64_t {
    return 0;
};

/** Returns a universal bitset */
template <typename T>
auto constexpr universal() -> T;

template <>
auto constexpr universal() -> std::uint64_t {
    // NOLINTNEXTLINE
    return 0xFFFFFFFFFFFFFFFF;
};

/** Checks if a bitset is empty */
template <typename T>
auto constexpr is_empty(T bitset) -> bool;

template <>
auto constexpr is_empty(std::uint64_t bitset) -> bool {
    return bitset == chester::engine::bitset::empty<std::uint64_t>();
};

/** Checks if a bitset is universal */
template <typename T>
auto constexpr is_universal(T bitset) -> bool;

template <>
auto constexpr is_universal(std::uint64_t bitset) -> bool {
    return bitset == chester::engine::bitset::universal<std::uint64_t>();
}

/** Checks if a bitset is single populated */
template <typename T>
auto constexpr is_single(T bitset) -> bool;

template <>
auto constexpr is_single(std::uint64_t bitset) -> bool {
    return bitset != 0 and (bitset & (bitset - 1)) == 0;
}

/** Returns the cardinality of a bitset */
template <typename T>
auto constexpr cardinality(T bitset) -> std::size_t;

template <>
auto constexpr cardinality(std::uint64_t bitset) -> std::size_t {
    std::size_t count = 0;
    while (bitset != 0) {
        count += 1;
        bitset &= bitset - 1;
    }
    return count;
}

/**
 * Returns the position of the first least significant set bit.
 *
 * In debug mode, this function asserts that the bitset is not empty.
 */
template <typename T>
auto constexpr scan_forward(T bitset) -> std::size_t;

template <>
auto constexpr scan_forward(std::uint64_t bitset) -> std::size_t {
#ifdef DEBUG
    if (chester::engine::bitset::is_empty(bitset)) {
        chester::panic("bitset is empty");
    }
#endif
    return std::countr_zero(bitset);
}

/**
 * Return the position of the first most significant set bit.
 *
 * In debug mode, this function asserts that the bitset is not empty.
 */
template <typename T>
auto constexpr scan_backward(T bitset) -> std::size_t;

template <>
auto constexpr scan_backward(std::uint64_t bitset) -> std::size_t {
#ifdef DEBUG
    if (chester::engine::bitset::is_empty(bitset)) {
        chester::panic("bitset is empty");
    }
#endif
    // NOLINTNEXTLINE
    return 63 - std::countl_zero(bitset);
}

/**
 * Removes the first least significant bit and returns its position.
 *
 * In debug mode, this function asserts that the bitset is not empty.
 */
template <typename T>
auto constexpr pop_front(T bitset) -> std::size_t;

template <>
auto constexpr pop_front(std::uint64_t *bitset) -> std::size_t {
#ifdef DEBUG
    if (chester::engine::bitset::is_empty(*bitset)) {
        chester::panic("bitset is empty");
    }
#endif
    const std::size_t index = chester::engine::bitset::scan_forward(*bitset);
    *bitset = *bitset ^ (1UL << index);
    return index;
}

/**
 * Removes the first most significant bit and returns its position.
 *
 * In debug mode, this function asserts that the bitset is not empty.
 */
template <typename T>
auto constexpr pop_back(T bitset) -> std::size_t;

template <>
auto constexpr pop_back(std::uint64_t *bitset) -> std::size_t {
#ifdef DEBUG
    if (chester::engine::bitset::is_empty(*bitset)) {
        chester::panic("bitset is empty");
    }
#endif
    const std::size_t index = chester::engine::bitset::scan_backward(*bitset);
    *bitset = *bitset ^ (1UL << index);
    return index;
}

/**
 * Returns the n-th subset of the given bitset.
 *
 * For performance, the bitset's cardinality is provided by the caller so
 * it is not recomputed for every subset. It goes without saying that providing
 * an incorrect cardinality results in undefined behavior.
 *
 * The `index` specifies which subset to return and must be within the range [0, 1 << cardinality).
 */
template <typename T>
auto constexpr subset(T bitset, std::size_t cardinality, std::size_t index) -> T;

template<>
auto constexpr subset(std::uint64_t bitset, std::size_t cardinality, std::size_t index) -> std::uint64_t {
#ifdef DEBUG
    if (cardinality != chester::engine::bitset::cardinality(bitset)) {
        chester::panic("provided bitset cardinality does not match its real cardinality");
    }

    if (index >= (1UL << cardinality)) {
        throw std::runtime_error("index is out of bounds");
    }
#endif

    std::uint64_t mask   = bitset;
    std::uint64_t result = 0;

    for (std::size_t i = 0; i < cardinality; ++i) {
        const std::size_t j = chester::engine::bitset::pop_front(&mask);
        if ((index & (1UL << i)) != 0) {
            result |= 1UL << j;
        }
    }

    return result;
}

} // namespace chester::engine::bitset
