#include <format>
#include <iostream>

auto main(int argc, char *argv[]) -> int {
    (void)argc, void(argv);

    // clang-format off
    std::cout <<
        std::format("Running {} v{}\n",
                    PROJECT_NAME,
                    PROJECT_VERSION);

    return 0;
}
