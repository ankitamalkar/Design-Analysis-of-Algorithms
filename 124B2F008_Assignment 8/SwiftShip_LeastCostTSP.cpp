// SwiftShip_LeastCostTSP.cpp
// Unique implementation of TSP using Branch and Bound (Least Cost Method)
// Case Study: Optimizing Delivery Routes for SwiftShip Logistics Company
// Author: Ankita Malkar

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Function to find the minimum edge cost from a given node
int firstMin(const vector<vector<int>>& cost, int i, int N) {
    int minVal = INF;
    for (int k = 0; k < N; k++)
        if (cost[i][k] != 0 && cost[i][k] < minVal)
            minVal = cost[i][k];
    return minVal;
}

// Function to find the second minimum edge cost from a given node
int secondMin(const vector<vector<int>>& cost, int i, int N) {
    int first = INF, second = INF;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;
        if (cost[i][j] <= first) {
            second = first;
            first = cost[i][j];
        } else if (cost[i][j] < second && cost[i][j] != first)
            second = cost[i][j];
    }
    return second;
}

int N;
int finalRes = INF;
vector<int> finalPath;

// Recursive Branch and Bound function
void TSPRec(const vector<vector<int>>& cost, vector<int>& currPath, vector<bool>& visited, int currBound, int currWeight, int level) {
    if (level == N) {
        if (cost[currPath[level - 1]][currPath[0]] != 0) {
            int currRes = currWeight + cost[currPath[level - 1]][currPath[0]];
            if (currRes < finalRes) {
                finalPath = currPath;
                finalPath.push_back(currPath[0]);
                finalRes = currRes;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (cost[currPath[level - 1]][i] != 0 && !visited[i]) {
            int temp = currBound;
            currWeight += cost[currPath[level - 1]][i];

            if (level == 1)
                currBound -= ((firstMin(cost, currPath[level - 1], N) + firstMin(cost, i, N)) / 2);
            else
                currBound -= ((secondMin(cost, currPath[level - 1], N) + firstMin(cost, i, N)) / 2);

            if (currBound + currWeight < finalRes) {
                currPath[level] = i;
                visited[i] = true;
                TSPRec(cost, currPath, visited, currBound, currWeight, level + 1);
            }

            currWeight -= cost[currPath[level - 1]][i];
            currBound = temp;
            fill(visited.begin(), visited.end(), false);
            for (int j = 0; j <= level - 1; j++)
                visited[currPath[j]] = true;
        }
    }
}

void TSP(const vector<vector<int>>& cost) {
    vector<int> currPath(N + 1, -1);
    vector<bool> visited(N, false);
    int currBound = 0;

    for (int i = 0; i < N; i++)
        currBound += (firstMin(cost, i, N) + secondMin(cost, i, N));

    currBound = (currBound & 1) ? currBound / 2 + 1 : currBound / 2;
    visited[0] = true;
    currPath[0] = 0;

    TSPRec(cost, currPath, visited, currBound, 0, 1);
}

int main() {
    cout << "SwiftShip Logistics - Least Cost Delivery Route Optimization\n";
    cout << "------------------------------------------------------------\n";

    cout << "Enter number of cities: ";
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(N));
    cout << "Enter the cost matrix (distance * fuel cost between cities):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> cost[i][j];

    TSP(cost);

    cout << "\nOptimal Delivery Route: ";
    for (int i = 0; i < N + 1; i++)
        cout << finalPath[i] << (i == N ? "" : " -> ");
    cout << "\nMinimum Delivery Cost: " << finalRes << "\n";

    return 0;
}
