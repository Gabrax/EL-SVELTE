#include <iostream>
#include <vector>

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
