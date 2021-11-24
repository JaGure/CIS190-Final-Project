all: a.out

a.out: main.cpp
	g++-10 -g -Wall -std=c++20 main.cpp `pkg-config gtkmm-4.0 --cflags`

test: a.out
	./a.out

clean:
	rm a.out