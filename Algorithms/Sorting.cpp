#include <iostream>
#include <vector>
#include <algorithm> // for std::sort

//C++ offers several sorting algorithms, both in the standard library and as part of various libraries and frameworks.
//Here, I'll provide examples of two common sorting algorithms: the std::sort function from the C++ Standard Library
//(which uses an optimized version of the introsort algorithm) and the classic bubble sort algorithm for educational purposes.

//Note: While bubble sort is simple to understand, it's not suitable for large datasets due to its poor time complexity (O(n^2)).
// In practice, you should use std::sort or other efficient sorting algorithms like quicksort or mergesort for real-world applications.

//std::sort (Introsort):
//The std::sort function is part of the C++ Standard Library (STL) and is highly optimized.
// It is recommended for most sorting tasks in C++ because of its performance.

int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}

//Bubble Sort (for educational purposes):
//
//Bubble sort is a simple sorting algorithm but not very efficient. It repeatedly steps through the list,
//compares adjacent elements, and swaps them if they are in the wrong order. The pass through the list is repeated until the list is sorted.
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        // After each pass, the largest element is at the end, so we can skip it
        --n;
    } while (swapped);
}

int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order using bubble sort
    bubbleSort(numbers);

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}
