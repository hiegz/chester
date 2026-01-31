cmake_minimum_required(VERSION 3.20)

# Export compile commands for LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_program(GPP_EXE g++)
if (GPP_EXE)
    message(STATUS "Found g++ : ${GPP_EXE}.")
elseif (NOT GPP_EXE)
    message(FATAL_ERROR "g++ not found in $PATH.")
endif()

project(
    chester
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_COMPILER ${GPP_EXE})
set(CMAKE_CXX_STANDARD 23) # C++23
set(CXX_COMPILE_OPTIONS -Werror -Wall -Wextra -Wpedantic)

include_directories(include)

#
# Engine
#

add_library(
    engine SHARED
    engine/lookup/moves/leaping.cpp
    engine/lookup/moves/sliding.cpp
    engine/lookup/in_between.cpp
    engine/bitboard.cpp
    engine/bitset.cpp
    engine/board.cpp
    engine/castling.cpp
    engine/castling_type.cpp
    engine/fen.cpp
    engine/file.cpp
    engine/piece.cpp
    engine/piece_type.cpp
    engine/position.cpp
    engine/rank.cpp
    engine/side.cpp
    engine/square.cpp
    engine/engine.cpp)

target_compile_options(
    engine
    PRIVATE ${CXX_COMPILE_OPTIONS})

target_compile_definitions(
    engine
    PUBLIC
        $<$<CONFIG:Debug>:DEBUG>)

#
# Frontend
#

add_executable(
    frontend
    frontend/frontend.cpp)

target_compile_options(
    frontend
    PRIVATE ${CXX_COMPILE_OPTIONS})

target_compile_definitions(
    frontend
    PUBLIC
        PROJECT_NAME="${PROJECT_NAME}"
        PROJECT_VERSION="${PROJECT_VERSION}"
        $<$<CONFIG:Debug>:DEBUG>)

#
# Tests
#

find_package(Catch2 3)

if (Catch2_FOUND)
    add_executable(
        tests
        tests/engine/lookup/moves/bishop.cpp
        tests/engine/lookup/moves/king.cpp
        tests/engine/lookup/moves/knight.cpp
        tests/engine/lookup/moves/rook.cpp
        tests/engine/lookup/in_between.cpp
        tests/engine/bitboard.cpp
        tests/engine/bitset.cpp
        tests/engine/castling.cpp
        tests/engine/fen.cpp
        tests/engine/file.cpp
        tests/engine/piece.cpp
        tests/engine/position.cpp
        tests/engine/rank.cpp
        tests/engine/square.cpp
        tests/tests.cpp)

    target_link_libraries(
        tests
        PRIVATE
            engine
            Catch2::Catch2WithMain)

    target_compile_options(
        tests
        PRIVATE ${CXX_COMPILE_OPTIONS})

    target_compile_definitions(
        tests
        PUBLIC
            $<$<CONFIG:Debug>:DEBUG>)
endif()
