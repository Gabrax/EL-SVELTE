#include <iostream>
#include <vector>

using namespace std;

// Swap two elements if they are not in order
void compAndSwap(vector<int>& arr, int i, int j, bool ascending) {
    if ((ascending && arr[i] > arr[j]) || (!ascending && arr[i] < arr[j])) {
        swap(arr[i], arr[j]);
    }
}

// Merging a bitonic sequence
void bitonicMerge(vector<int>& arr, int low, int size, bool ascending) {
    if (size <= 1) return;

    int mid = size / 2;
    for (int i = low; i < low + mid; i++) {
        compAndSwap(arr, i, i + mid, ascending);
    }

    bitonicMerge(arr, low, mid, ascending);
    bitonicMerge(arr, low + mid, mid, ascending);
}

// Generating a bitonic sequence and sorting it
void bitonicSort(vector<int>& arr, int low, int size, bool ascending) {
    if (size <= 1) return;

    int mid = size / 2;

    // First half in ascending order
    bitonicSort(arr, low, mid, true);
    // Second half in descending order
    bitonicSort(arr, low + mid, mid, false);

    // Merge whole sequence in ascending or descending order
    bitonicMerge(arr, low, size, ascending);
}

// Wrapper function for bitonic sort
void sortBitonic(vector<int>& arr, bool ascending = true) {
    bitonicSort(arr, 0, arr.size(), ascending);
}

int main() {
    vector<int> arr = {3, 7, 4, 8, 6, 2, 1, 5};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    sortBitonic(arr);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
}
