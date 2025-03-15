#include "dijkstras.h"

int main(int argc, char * argv[]){
    Graph G;
    string filename = get_arg(argc, argv, "src/small.txt");
    file_to_graph(filename, G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    int destination = 4;
    vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(path, distances[destination]);

    return 0;
}