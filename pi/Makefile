all: app

#CFLAGS := -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -std=c++14 -I../.. `pkg-config gtkmm-3.0 --cflags --libs`
CFLAGS :=  -std=c++14 -I.. `pkg-config gtkmm-3.0 --cflags --libs`


app: main.cpp Fenetre.cpp
	@echo "======== Compiling $^ to $@ ========"
	g++ -o $@ $^ ${CFLAGS}


.PHONY: clean
clean:
	rm -f app *.o
