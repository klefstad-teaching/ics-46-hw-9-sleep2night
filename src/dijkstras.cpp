#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, UNDEFINED); 
    priority_queue<pair<int, int>> minHeap; 
    
    distances[source] = 0;
    minHeap.push({source, 0});

    while(!minHeap.empty()){
        int u = minHeap.top().first;
        minHeap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    if(distances[destination] == INF) return path;
    for(int v = destination; v != UNDEFINED; v = previous[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    if(v.empty()) return;
    for(size_t i = 0; i<v.size(); ++i) cout << v[i] << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}

string get_arg(int argc, char * argv[], string def){
    if(argc > 1) return argv[1];
    return def;
}