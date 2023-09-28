#include <iostream>
#include <vector>
//Vectors are a versatile data structure and are widely used in C++ for managing collections of data with dynamic sizes.
// They automatically handle memory allocation and deallocation

int main()
{
    //Declare a vector:
    std::vector<int> myVector;
    //Adding elements:
    myVector.push_back(42);
    myVector.push_back(17);
    //Accessing elements:
    //Note: Using at() is safer than [] because it performs bounds checking and throws an exception if the index is out of range.
    int firstElement = myVector[0];
    int secondElement = myVector.at(1);
    //Getting the size:
    int size = myVector.size();
    //Iterating through a vector:
    for (int i = 0; i < myVector.size(); ++i) {
        std::cout << myVector[i] << '\n';
    }

    // Alternatively, using a range-based for loop (C++11 and later):
    for (int element : myVector) {
        std::cout << element << '\n';
    }
    //Removing elements:
    myVector.pop_back(); // Removes the last element
    myVector.erase(myVector.begin() + 1); // Removes the element at index 1
    //Resizing the vector:
    myVector.resize(10); // Resize to contain 10 elements
    //Clearing the vector:
    myVector.clear();

}
