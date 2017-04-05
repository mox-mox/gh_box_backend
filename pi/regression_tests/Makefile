

CFLAGS := -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c++14 -I../..


all: main

main: main.cpp
	g++ ${CFLAGS} -o $@ $^

regression_tests: regression_main.cpp regression.cpp
	g++ ${CFLAGS} -o $@ $^



.PHONY: clean
clean:
	rm -f main regression_tests
