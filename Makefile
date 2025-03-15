F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
P = main
G = graph

def: $G

main: src/ladder_main.cpp src/ladder.cpp
	g++ $F src/ladder_main.cpp src/ladder.cpp -o main

graph: src/dijkstras_main.cpp src/dijkstras.cpp
	g++ $F src/dijkstras_main.cpp src/dijkstras.cpp -o graph

clean:
	/bin/rm -f $P $G *.o

