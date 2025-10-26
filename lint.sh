#!/bin/bash

run-clang-tidy -p build/debug
cppcheck -Iinclude --force --enable=all --suppress=missingIncludeSystem --inline-suppr engine tests frontend
