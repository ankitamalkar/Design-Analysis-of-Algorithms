#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

const int INF = numeric_limits<int>::max();

// Edge structure
struct Edge {
    int to;
    int weight;
};

// Graph class
class Graph {
private:
    int V; // Number of intersections
    vector<vector<Edge>> adj;

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // Add or update an edge (dynamic weights)
    void addOrUpdateEdge(int u, int v, int w) {
        bool updated = false;
        for (auto &edge : adj[u]) {
            if (edge.to == v) {
                edge.weight = w; // update weight
                updated = true;
                break;
            }
        }
        if (!updated) adj[u].push_back({v, w});

        // For undirected graph, update reverse edge
        updated = false;
        for (auto &edge : adj[v]) {
            if (edge.to == u) {
                edge.weight = w;
                updated = true;
                break;
            }
        }
        if (!updated) adj[v].push_back({u, w});
    }

    // Dijkstra's algorithm from source
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF);
        dist[src] = 0;

        // Min-heap: pair(distance, node)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue; // Skip outdated distance

            for (auto &edge : adj[u]) {
                int v = edge.to, w = edge.weight;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Function to display shortest path distances from source
    void displayDistances(const vector<int>& dist, int src) {
        cout << "\nShortest travel time from Intersection " << src << ":\n";
        cout << left << setw(15) << "Intersection" << setw(15) << "Time(min)" << endl;
        cout << string(30, '-') << endl;
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INF)
                cout << setw(15) << i << setw(15) << "INF" << endl;
            else
                cout << setw(15) << i << setw(15) << dist[i] << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of intersections and roads: ";
    cin >> V >> E;

    Graph city(V);

    cout << "Enter road details (u v travel_time):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        city.addOrUpdateEdge(u, v, w);
    }

    int source;
    cout << "Enter ambulance current location (source intersection): ";
    cin >> source;

    vector<int> distances = city.dijkstra(source);
    city.displayDistances(distances, source);

    // Example: Dynamic weight update (traffic congestion changes)
    char choice;
    do {
        cout << "\nDo you want to update a road travel time? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int u, v, w;
            cout << "Enter road u v new_travel_time: ";
            cin >> u >> v >> w;
            city.addOrUpdateEdge(u, v, w);

            // Recompute shortest paths
            distances = city.dijkstra(source);
            city.displayDistances(distances, source);
        }
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
