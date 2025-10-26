default:

clang-tidy:
	run-clang-tidy -p build/debug

cppcheck:
	cppcheck -Iinclude --force --enable=all --suppress=missingIncludeSystem --inline-suppr engine tests frontend

lint: clang-tidy cppcheck
