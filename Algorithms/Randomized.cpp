#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Randomized algorithms in C++ are algorithms that use randomization as a key component to achieve certain desirable properties or improve their efficiency.
// Randomized algorithms are particularly useful in situations where a deterministic algorithm might be too slow or impractical.
//
//Here's a simple example of a randomized algorithm in C++: the Randomized QuickSort algorithm. QuickSort is a popular sorting algorithm,
// and the randomized version introduces randomness to improve its average-case performance.

//In this example, the Randomized QuickSort algorithm chooses a random pivot element during the partitioning step.
// This randomization helps ensure that the algorithm's performance is less predictable, which is often a desirable property in practice.

// Function to partition the array using a random pivot element
int partition(vector<int>& arr, int low, int high) {
    // Generate a random index between low and high
    int randomIndex = low + rand() % (high - low + 1);

    // Swap the pivot element (chosen randomly) with the last element
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized QuickSort algorithm
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    // Seed the random number generator
    srand(time(0));

    vector<int> arr = {12, 4, 5, 6, 7, 3, 1, 15};
    int n = arr.size();

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    randomizedQuickSort(arr, 0, n - 1);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
