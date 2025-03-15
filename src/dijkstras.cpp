#include "dijkstras.h"
#include <algorithm>
#include <stack>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> min_distance(G.numVertices, INF);
    min_distance[source] = 0;
    previous.assign(G.numVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> vertex_queue;
    vertex_queue.emplace(0, source);

    while (!vertex_queue.empty()) {
        auto current = vertex_queue.top();
        vertex_queue.pop();
        
        int u = current.second;
        int current_dist = current.first;

        if (current_dist > min_distance[u]) 
            continue;

        for (const Edge& e : G[u]) {
            int updated_dist = min_distance[u] + e.weight;
            if (updated_dist < min_distance[e.dst]) {
                min_distance[e.dst] = updated_dist;
                previous[e.dst] = u;
                vertex_queue.emplace(updated_dist, e.dst);
            }
        }
    }
    return min_distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    stack<int> path_stack;
    for (int node = destination; node != -1; node = previous[node]) {
        path_stack.push(node);
    }

    vector<int> path;
    while (!path_stack.empty()) {
        path.push_back(path_stack.top());
        path_stack.pop();
    }

    if (!path.empty()) {
        print_path(path, distances[destination]);
    }
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) return;
    
    cout << path[0];
    for (size_t i = 1; i < path.size(); ++i) {
        cout << " " << path[i];
    }
    cout << "\nTotal cost is " << total_cost << endl;
}
