#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("src/large.txt", G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    // int destination = 4;
    // vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(distances, G.numVertices);

    return 0;
}