#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

const int INF = numeric_limits<int>::max();

// Structure to represent a route between nodes
struct Edge {
    int to;       // Destination node
    int cost;     // Cost or time to travel
};

// Function to compute shortest path in a multistage graph using DP
void multistageGraphOptimalPath(const vector<vector<vector<Edge>>>& stages) {
    int N = stages.size(); // Number of stages
    vector<vector<int>> dp(N);       // dp[i][j] = min cost to reach stage N from node j in stage i
    vector<vector<int>> nextNode(N); // nextNode[i][j] = next node in optimal path

    // Initialize DP for last stage (cost = 0 to destination itself)
    int lastStageSize = stages[N - 1].size();
    dp[N - 1] = vector<int>(lastStageSize, 0);
    nextNode[N - 1] = vector<int>(lastStageSize, -1);

    // Compute DP from second last stage backwards
    for (int stage = N - 2; stage >= 0; --stage) {
        int size = stages[stage].size();
        dp[stage] = vector<int>(size, INF);
        nextNode[stage] = vector<int>(size, -1);

        for (int u = 0; u < size; ++u) {
            for (const Edge &e : stages[stage][u]) {
                int costThroughE = e.cost + dp[stage + 1][e.to];
                if (costThroughE < dp[stage][u]) {
                    dp[stage][u] = costThroughE;
                    nextNode[stage][u] = e.to;
                }
            }
        }
    }

    // Display optimal cost from each starting node in stage 0
    cout << fixed << setprecision(2);
    cout << "\nOptimal delivery costs from Stage 0 nodes:\n";
    for (int i = 0; i < dp[0].size(); ++i)
        cout << "Start node " << i << ": Cost = " << dp[0][i] << endl;

    // Example: Print one optimal path from first node of stage 0
    cout << "\nOne optimal delivery path starting from node 0:\n";
    int currentNode = 0;
    for (int stage = 0; stage < N; ++stage) {
        cout << "Stage " << stage << " Node " << currentNode;
        if (stage != N - 1) cout << " -> ";
        currentNode = nextNode[stage][currentNode];
    }
    cout << endl;
}

int main() {
    int N; // Number of stages
    cout << "Enter number of stages: ";
    cin >> N;

    vector<vector<vector<Edge>>> stages(N);

    // Input number of nodes in each stage
    for (int stage = 0; stage < N; ++stage) {
        int numNodes;
        cout << "Enter number of nodes in Stage " << stage << ": ";
        cin >> numNodes;
        stages[stage].resize(numNodes);
    }

    // Input edges between consecutive stages
    cout << "Enter edges (fromNode toNode cost) between consecutive stages:\n";
    for (int stage = 0; stage < N - 1; ++stage) {
        cout << "Stage " << stage << " to Stage " << stage + 1 << ":\n";
        for (int u = 0; u < stages[stage].size(); ++u) {
            int numEdges;
            cout << "Number of outgoing edges from node " << u << ": ";
            cin >> numEdges;
            for (int e = 0; e < numEdges; ++e) {
                int v, cost;
                cin >> v >> cost;
                stages[stage][u].push_back({v, cost});
            }
        }
    }

    // Compute optimal paths
    multistageGraphOptimalPath(stages);

    return 0;
}
