#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to represent an item
struct Item {
    double weight;
    double value;

    double ratio() const {
        return value / weight; // Value per unit weight
    }
};

// Function to perform Fractional Knapsack
double fractionalKnapsack(vector<Item>& items, double capacity) {
    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio() > b.ratio();
    });

    double totalValue = 0.0;
    for (const auto& item : items) {
        if (capacity <= 0) break;

        if (item.weight <= capacity) {
            // Take the whole item
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            // Take fraction of the item
            double fraction = capacity / item.weight;
            totalValue += item.value * fraction;
            capacity = 0; // Knapsack full
        }
    }

    return totalValue;
}

int main() {
    int n;
    double capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(items, capacity);

    cout << fixed << setprecision(2);
    cout << "Maximum value that can be carried: " << maxValue << endl;

    return 0;
}

