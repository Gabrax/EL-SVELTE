#include <iostream>

//In C++, an array is a collection of elements of the same data type stored in contiguous memory locations.
// Arrays are one of the fundamental data structures in C++ and provide a way
// to store and access multiple values of the same type under a single variable name.

int main()
{
    // Declaring an Array:
    int myArray[5];
    //Initializing an Array:

    ///Static Initialization: Initialize the array when declaring it.
    int myArray[5] = {1, 2, 3, 4, 5};
    ///Dynamic Initialization: Initialize the array later in your code.
    int myArray[5];
    myArray[0] = 1;
    myArray[1] = 2;
    myArray[2] = 3;
    myArray[3] = 4;
    myArray[4] = 5;
    ///Partial Initialization: You can initialize only some elements of the array,
    /// and the rest will be set to default values (0 for integers).
    int myArray[5] = {1, 2}; // Initializes the first two elements to 1 and 2, and the rest to 0.
    //Accessing Array Elements:
    int value = myArray[2]; // Accesses the third element (index 2) of the array.
    //Array Size:
    int size = sizeof(myArray) / sizeof(myArray[0]);
// OR
    int size = std::size(myArray); // C++17 and later
    //Array Iteration:
    for (int i = 0; i<10;i++)
    {
        std::cout << myArray[i] << '\n';
    }
    for(int x : arr)
    {
        std::cout << x << '\n';
    }
    for (const auto &var : arr)
    {
        std::cout << var << '\n';
    }
    //Multidimensional Arrays:
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};




}
