#include <iostream>
#include <vector>
//Depending on your specific requirements and data structures, you might use other algorithms like interpolation search,
// hash tables, or tree-based search algorithms such as binary search trees or balanced trees like AVL or Red-Black trees.

//Linear Search:

//Linear search is a simple algorithm that iterates through an array or container to find a specific element.
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i; // Element found at index i
        }
    }
    return -1; // Element not found
}

int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // Element found at index i
        }
    }
    return -1; // Element not found
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

  std::cout << linearSearch(arr, size, 3);
}

