#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, UNDEFINED); 
    priority_queue<pair<int, int>> minHeap; 
    
    distances[source] = 0;
    minHeap.push({0, source});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    int current = destination;
    while(current != -1){
        path.push_back(current);
        current = previous[current];
    }

    if(path.back() != 0 || distances[path.back()] == INF) return {};
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    if(v.empty()) return;
    for(size_t i = 0; i<v.size(); ++i) cout << v[i] << " ";
    cout << endl;
    cout << total << endl;
}