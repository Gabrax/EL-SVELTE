#include <queue>
#include <iostream>

//In C++, a heap is a data structure that is often used to implement priority queues and dynamic memory allocation.
// It is not to be confused with the heap data structure used in computer science,
// which typically refers to a binary heap or a more general tree-based structure.

//This is useful for implementing data structures and algorithms that require efficient access to the maximum (or minimum) element.
//
//In both cases, it's crucial to manage memory properly to avoid memory leaks,
// and for data structures, to ensure that the heap property (max-heap or min-heap) is maintained as elements are added or removed.
//
//If you need more control or want to implement your own heap data structure,
// you can do so by managing memory manually and implementing the necessary operations (e.g., insert, extract, heapify) as per your requirements.
// This often involves using arrays or linked structures to represent the heap.

//Dynamic Memory Allocation:
// The C++ standard library provides operators new and delete (or malloc and free)
// for dynamic memory allocation and deallocation on the heap. Here's an example:

int* myInt = new int; // Allocates an integer on the heap
*myInt = 42;
delete myInt; // Deallocates the memory when done

//This allows you to allocate memory as needed during the program's execution and free it when you're done with it.
// It's important to remember to free allocated memory to avoid memory leaks.

//Priority Queue: The C++ standard library also provides a priority_queue container,
// which is implemented as a max-heap by default (you can change it to a min-heap by providing a custom comparator).
// Here's an example of using priority_queue:

int main() {
    std::priority_queue<int> maxHeap;

    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);

    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " "; // Outputs 30 20 10 (in descending order)
        maxHeap.pop();
    }

    return 0;
}