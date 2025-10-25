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
set(CMAKE_CXX_STANDARD 20) # C++20
set(CXX_COMPILE_OPTIONS -Werror -Wall -Wextra -Wpedantic)

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
        tests/tests.cpp)

    target_link_libraries(
        tests
        PRIVATE Catch2::Catch2WithMain)

    target_compile_options(
        tests
        PRIVATE ${CXX_COMPILE_OPTIONS})
endif()
