default:

clang-tidy:
	run-clang-tidy -p build/debug

cppcheck:
	cppcheck -Iinclude --force --check-level=exhaustive --enable=all --suppress=missingIncludeSystem --inline-suppr engine tests frontend

lint: clang-tidy cppcheck
