default:

clang-tidy:
	run-clang-tidy -p build/debug

cppcheck:
	cppcheck \
		-Iinclude \
		--force \
		--check-level=exhaustive \
		--enable=all \
		--suppress=missingIncludeSystem \
		--suppress=uninitMemberVar \
		--suppress=noExplicitConstructor \
		--suppress=duplicateExpression \
		--inline-suppr \
		engine tests frontend

lint: clang-tidy cppcheck
