#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

// Structure to represent an item
struct Item {
    string name;   // Name of the supply
    int weight;    // Weight in kg
    int value;     // Utility/importance
    int priority;  // Higher value = more critical
};

// Function to solve 0/1 Knapsack using Dynamic Programming
int knapsackDP(const vector<Item>& items, int W, vector<int>& selectedItems) {
    int N = items.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value + items[i - 1].priority
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtrack to find selected items
    int w = W;
    for (int i = N; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }

    return dp[N][W];
}

int main() {
    int N, W;
    cout << "Enter number of items and truck capacity (kg): ";
    cin >> N >> W;

    vector<Item> items(N);
    cout << "Enter details for each item:\n";
    cout << "(Name Weight Value Priority[1-High,0-Low])\n";

    for (int i = 0; i < N; ++i) {
        cin >> items[i].name >> items[i].weight >> items[i].value >> items[i].priority;
    }

    vector<int> selectedItems;
    int maxUtility = knapsackDP(items, W, selectedItems);

    cout << "\nMaximum total utility (value + priority) achievable: " << maxUtility << endl;

    cout << "\nSelected items for the truck:\n";
    cout << left << setw(15) << "Name" << setw(10) << "Weight" << setw(10) << "Value" << setw(10) << "Priority" << endl;
    cout << string(45, '-') << endl;
    for (int idx : selectedItems) {
        cout << left << setw(15) << items[idx].name
             << setw(10) << items[idx].weight
             << setw(10) << items[idx].value
             << setw(10) << items[idx].priority << endl;
    }

    return 0;
}
