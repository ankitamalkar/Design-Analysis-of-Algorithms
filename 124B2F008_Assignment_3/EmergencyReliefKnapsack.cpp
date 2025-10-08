#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure to represent each relief item
struct ReliefItem {
    string name;
    double weight;
    double value;
    bool divisible;

    // Utility ratio (value per unit weight)
    double ratio() const {
        return value / weight;
    }
};

// Function to perform Fractional Knapsack optimization
double maximizeUtility(vector<ReliefItem> &items, double maxWeight) {
    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), [](const ReliefItem &a, const ReliefItem &b) {
        return a.ratio() > b.ratio();
    });

    double totalUtility = 0.0;
    double currentWeight = 0.0;

    cout << "\n--- Selected Items for Transport ---\n";
    cout << left << setw(15) << "Item"
         << setw(12) << "Taken(kg)"
         << setw(12) << "Value"
         << setw(12) << "Type" << endl;
    cout << string(50, '-') << endl;

    for (const auto &item : items) {
        if (currentWeight >= maxWeight)
            break;

        if (currentWeight + item.weight <= maxWeight) {
            // Take the entire item
            currentWeight += item.weight;
            totalUtility += item.value;

            cout << left << setw(15) << item.name
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << (item.divisible ? "Divisible" : "Whole") << endl;
        } 
        else if (item.divisible) {
            // Take a fractional part of divisible item
            double remaining = maxWeight - currentWeight;
            double fraction = remaining / item.weight;
            double partialValue = item.value * fraction;

            totalUtility += partialValue;
            currentWeight = maxWeight;

            cout << left << setw(15) << item.name
                 << setw(12) << remaining
                 << setw(12) << fixed << setprecision(2) << partialValue
                 << setw(12) << "Fraction" << endl;
        }
    }

    cout << "\nTotal Utility Value: " << fixed << setprecision(2) << totalUtility << endl;
    cout << "Total Weight Loaded: " << currentWeight << " / " << maxWeight << " kg\n";
    return totalUtility;
}

int main() {
    int n;
    double boatCapacity;

    cout << "===== Emergency Relief Supply Distribution =====\n";
    cout << "Enter number of relief items: ";
    cin >> n;

    vector<ReliefItem> items(n);

    cout << "\nEnter details for each item:\n";
    cout << "(Name Weight Value Divisible[1 for Yes, 0 for No])\n";

    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].name >> items[i].weight >> items[i].value;
        int div;
        cin >> div;
        items[i].divisible = (div == 1);
    }

    cout << "\nEnter boat weight capacity (kg): ";
    cin >> boatCapacity;

    maximizeUtility(items, boatCapacity);

    cout << "\nOperation Summary: Relief supplies successfully optimized for transport.\n";
    return 0;
}
