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

//std::stable_sort: Similar to std::sort, but maintains the relative order of elements with equal values.
int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order
    std::stable_sort(numbers.begin(), numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}

//std::partial_sort: Sorts the specified range such that the first N elements are sorted in ascending order.
int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order
    std::partial_sort(numbers.begin(), numbers.begin() + N, numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}

//std::partial_sort_copy: Copies and partially sorts elements from the input range to the output range.
int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order
    std::partial_sort_copy(numbers.begin(), numbers.end(), numbers.begin(), numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}

//std::nth_element: Rearranges elements in such a way that the element at the N-th position is the element that would be in that position in a sorted sequence.
int main() {
    std::vector<int> numbers = {5, 2, 9, 3, 6};

    // Sort the vector in ascending order
    std::nth_element(numbers.begin(), numbers.begin() + N, numbers.end());


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

// Merge two sorted subarrays into one sorted array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = arr[middle + 1 + i];
    }

    // Merge the temporary arrays back into arr[left...right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k++] = leftArray[i++];
        } else {
            arr[k++] = rightArray[j++];
        }
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < n1) {
        arr[k++] = leftArray[i++];
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2) {
        arr[k++] = rightArray[j++];
    }
}

// Recursive function to perform merge sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

//This code defines the mergeSort function for sorting an array using the merge sort algorithm.
// It recursively divides the array into two halves until the base case is reached (i.e., the array has only one element).
// Then, it merges the sorted halves to produce the final sorted array.
// The merge function is used to merge two sorted subarrays.
