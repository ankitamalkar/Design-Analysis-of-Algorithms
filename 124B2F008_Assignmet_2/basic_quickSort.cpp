#include <iostream>
using namespace std;

// ------------------------------
// Partition Function
// ------------------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // first element as pivot
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= high && arr[i] >= pivot) i++; // descending order
        while (j >= low + 1 && arr[j] < pivot) j--;
        if (i < j)
            swap(arr[i], arr[j]);
        else
            break;
    }

    swap(arr[low], arr[j]);
    return j;
}

// ------------------------------
// Quicksort Function
// ------------------------------
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ------------------------------
// Main Function
// ------------------------------
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    quickSort(arr, 0, n - 1);

    cout << "\nSorted array in descending order:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
