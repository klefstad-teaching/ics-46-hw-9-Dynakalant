#include "dijkstras.h"

struct Node {
    int vertex;
    int weight;
};

struct NodeLT {
    bool operator()(const Node& l, const Node& r) { return l.weight < r.weight; }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();

    vector<int> distance(n, INF);

    previous = vector<int>(n, -1);

    vector<bool> visited(n, false);

    std::priority_queue<Node, std::vector<Node>, NodeLT> pq;

    pq.push(Node(source, 0));

    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    std::stack<int> path_q;
    std::vector<int> shortest_path;
    int u = destination;
    while (u != -1) {
        path_q.push(u);
        u = previous[u];
    }
    while (!path_q.empty()) {
        shortest_path.push_back(path_q.top());
        path_q.pop();
    }
    return shortest_path;
}

void print_path(const vector<int>& v, int total) {
    for (int n : v) std::cout << n << ' ';
    std::cout << '\n' << "Total cost is " << total << '\n';
}

