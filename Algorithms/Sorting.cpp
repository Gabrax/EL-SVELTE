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



