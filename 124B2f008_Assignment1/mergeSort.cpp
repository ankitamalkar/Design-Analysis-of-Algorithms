#include <bits/stdc++.h>
using namespace std;

// ------------------------------
// Structure to represent an Order
// ------------------------------
struct Order {
    int orderId;
    long long timestamp;   // store as integer for efficiency (e.g., Unix time)
    string customerName;
};

// Utility function to print orders (for debugging/testing)
void printOrders(const vector<Order> &orders, int limit = 10) {
    for (int i = 0; i < min(limit, (int)orders.size()); i++) {
        cout << "OrderID: " << orders[i].orderId
             << ", Timestamp: " << orders[i].timestamp
             << ", Customer: " << orders[i].customerName << "\n";
    }
}

// ------------------------------
// Merge Function (for Merge Sort)
// ------------------------------
void merge(vector<Order> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge back into arr by timestamp
    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// ------------------------------
// Merge Sort Implementation
// ------------------------------
void mergeSort(vector<Order> &arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ------------------------------
// Dataset Generator
// ------------------------------
vector<Order> generateOrders(int n) {
    vector<Order> orders;
    orders.reserve(n);

    srand(time(0));
    long long baseTime = 1700000000; // some base timestamp

    for (int i = 0; i < n; i++) {
        Order o;
        o.orderId = i;
        o.timestamp = baseTime + rand() % 1000000; // random timestamp offset
        o.customerName = "Customer_" + to_string(i);
        orders.push_back(o);
    }
    return orders;
}

// ------------------------------
// Main Function
// ------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 1000000; // 1 million orders
    cout << "Generating " << n << " random orders...\n";
    vector<Order> orders = generateOrders(n);
    vector<Order> ordersCopy = orders; // duplicate for std::sort comparison

    // ------------------------------
    // Sorting with Merge Sort
    // ------------------------------
    auto start = chrono::high_resolution_clock::now();
    mergeSort(orders, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> mergeSortTime = end - start;

    cout << "Merge Sort completed in " << mergeSortTime.count() << " seconds.\n";

    // ------------------------------
    // Sorting with std::sort (Timsort/Introsort)
    // ------------------------------
    start = chrono::high_resolution_clock::now();
    sort(ordersCopy.begin(), ordersCopy.end(), [](const Order &a, const Order &b) {
        return a.timestamp < b.timestamp;
    });
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> builtinSortTime = end - start;

    cout << "std::sort completed in " << builtinSortTime.count() << " seconds.\n";

    // Print first 5 sorted orders for verification
    cout << "\nFirst 5 sorted orders (by Merge Sort):\n";
    printOrders(orders, 5);

    return 0;
}

/*
--------------------------------------------------
Time Complexity Analysis:
--------------------------------------------------
- Merge Sort:
    Best Case:   O(n log n)
    Average Case: O(n log n)
    Worst Case:   O(n log n)
    Space Complexity: O(n) (extra arrays for merging)

- std::sort in C++:
    Usually Introsort (QuickSort + HeapSort + InsertionSort hybrid)
    Average Case: O(n log n)
    Worst Case:   O(n log n)
    Space Complexity: O(log n)

--------------------------------------------------
Comparison:
--------------------------------------------------
- Bubble/Selection/Insertion Sort → O(n^2), not feasible for 1M records.
- Merge Sort → Stable, predictable O(n log n), good for large datasets.
- std::sort → Usually faster in practice due to hybrid optimizations.
--------------------------------------------------
*/
