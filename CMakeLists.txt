cmake_minimum_required(VERSION 3.26)
project(Data_Structures_and_Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA DataStructures/Arrays.cpp
        DataStructures/Singular_Linked_Lists.cpp
        DataStructures/Stack.cpp
        DataStructures/Queue.cpp
        DataStructures/Tree.cpp
        DataStructures/Graph.cpp
        Algorithms/Brute_Force.cpp
        Algorithms/Recursive.cpp
        Algorithms/Randomized.cpp
        Algorithms/Sorting.cpp
        Algorithms/Searching.cpp
        Algorithms/Hashing.cpp
        DataStructures/Vector.cpp
        DataStructures/Doubly_Linked_Lists.cpp
        DataStructures/Circular_Linked_LIsts.cpp
        Algorithms/Breadth_First_Search.cpp
        Algorithms/Binary_Search_Tree.cpp
        DataStructures/Heap-PriorityQueue.cpp
)
