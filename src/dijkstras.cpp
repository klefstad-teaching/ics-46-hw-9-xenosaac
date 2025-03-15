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
        auto [dist, u] = vertex_queue.top();
        vertex_queue.pop();

        if (dist > min_distance[u]) continue;

        for (const Edge& e : G[u]) {
            int v = e.dst, weight = e.weight;
            int new_dist = dist + weight;

            if (new_dist < min_distance[v]) {
                min_distance[v] = new_dist;
                previous[v] = u;
                vertex_queue.emplace(new_dist, v);
            }
        }
    }
    return min_distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    if (!path.empty()) {
        print_path(path, distances[destination]);
    }
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "\nTotal cost is " << total_cost << endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total_cost << endl;
}