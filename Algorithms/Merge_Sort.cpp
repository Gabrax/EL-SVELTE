#include <iostream>
#include <vector>

//This code defines the mergeSort function for sorting an array using the merge sort algorithm.
// It recursively divides the array into two halves until the base case is reached (i.e., the array has only one element).
// Then, it merges the sorted halves to produce the final sorted array.
// The merge function is used to merge two sorted subarrays.

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

