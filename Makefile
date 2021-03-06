all: a.out

a.out: main.cpp board.hpp board.cpp game.hpp game.cpp
	g++-10 -g -Wall -std=c++20 main.cpp -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

client: main.cpp board.hpp board.cpp game.hpp game.cpp piece.hpp piece.cpp consts.hpp
	clang++ -std=c++2a main.cpp board.cpp game.cpp piece.cpp -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o client

server: server.cpp
	clang++ -std=c++2a server.cpp -I/usr/local/include -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o server

test: a.out
	./a.out

clean:
	rm server
	rm client