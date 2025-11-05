#include <bits/stdc++.h>
using namespace std;

struct Order {
    int orderId;
    long long timestamp;
    string customerName;
};

void printOrders(const vector<Order> &orders, int limit = 10) {
    for (int i = 0; i < min(limit, (int)orders.size()); i++) {
        cout << "OrderID: " << orders[i].orderId
             << ", Timestamp: " << orders[i].timestamp
             << ", Customer: " << orders[i].customerName << "\n";
    }
}

void merge(vector<Order> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Order> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<Order> &arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

vector<Order> generateOrders(int n) {
    vector<Order> orders;
    orders.reserve(n);
    srand(time(0));
    long long baseTime = 1700000000;
    for (int i = 0; i < n; i++) {
        Order o;
        o.orderId = i;
        o.timestamp = baseTime + rand() % 1000000;
        o.customerName = "Customer_" + to_string(i);
        orders.push_back(o);
    }
    return orders;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 1000000;
    cout << "Generating " << n << " random orders...\n";
    vector<Order> orders = generateOrders(n);
    vector<Order> ordersCopy = orders;
    auto start = chrono::high_resolution_clock::now();
    mergeSort(orders, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> mergeSortTime = end - start;
    cout << "Merge Sort completed in " << mergeSortTime.count() << " seconds.\n";
    start = chrono::high_resolution_clock::now();
    sort(ordersCopy.begin(), ordersCopy.end(), [](const Order &a, const Order &b) {
        return a.timestamp < b.timestamp;
    });
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> builtinSortTime = end - start;
    cout << "std::sort completed in " << builtinSortTime.count() << " seconds.\n";
    cout << "\nFirst 5 sorted orders (by Merge Sort):\n";
    printOrders(orders, 5);
    return 0;
}
