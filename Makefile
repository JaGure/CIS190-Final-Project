all: a.out

a.out: main.cpp board.hpp board.cpp
	g++-10 -g -Wall -std=c++20 main.cpp -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

works: main.cpp board.hpp board.cpp
	clang++ -g -Wall -std=c++20 main.cpp board.cpp -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

test: a.out
	./a.out

clean:
	rm a.out