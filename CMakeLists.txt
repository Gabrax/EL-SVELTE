cmake_minimum_required(VERSION 3.26)
project(Data_Structures_and_Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA DataStructures/Arrays.cpp
        DataStructures/Linked_Lists.cpp
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
)
