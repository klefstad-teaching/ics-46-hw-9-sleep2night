F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
P = ladder
G = graph

def: $P

ladder: src/ladder_main.cpp src/ladder.cpp src/ladder.h
	g++ $F src/ladder_main.cpp src/ladder.cpp -o ladder

graph: src/dijkstras_main.cpp src/dijkstras.cpp src/dijkstras.h
	g++ $F src/dijkstras_main.cpp src/dijkstras.cpp -o graph

clean:
	/bin/rm -f $P $G main output *.o

