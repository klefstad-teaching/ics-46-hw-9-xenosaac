#include "dijkstras.h"
#include <algorithm>
#include <stack>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> min_distance(G.numVertices, INF);
    min_distance[source] = 0;
    previous.assign(G.numVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> vertex_queue;
    vertex_queue.emplace(0, source);

    for (; !vertex_queue.empty(); vertex_queue.pop()) {
        auto current_node = vertex_queue.top();
        int current_dist = current_node.first;
        int u = current_node.second;

        if (current_dist > min_distance[u]) continue;

        auto edges_begin = G[u].begin();
        auto edges_end = G[u].end();
        for (auto edge_it = edges_begin; edge_it != edges_end; ++edge_it) {
            const Edge& e = *edge_it;
            int v = e.dst;
            int alt_path = current_dist + e.weight;
            
            if (alt_path < min_distance[v]) {
                min_distance[v] = alt_path;
                previous[v] = u;
                vertex_queue.emplace(alt_path, v);
            }
        }
    }
    return min_distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int current_node = destination; current_node != -1; current_node = previous[current_node]) {
        path.emplace_back(current_node);
    }
    reverse(path.begin(), path.end());

    if (!path.empty()) {
        print_path(path, distances[destination]);
    }
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "Total cost is " << total_cost << endl;
        return;
    }
    
    cout << path[0];
    for (size_t i = 1; i < path.size(); ++i) {
        cout << " " << path[i];
    }
    cout << "\nTotal cost is " << total_cost << endl;
}