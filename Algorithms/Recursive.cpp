#include <iostream>

//A recursive algorithm in C++ is an algorithm that solves a problem by breaking it down into smaller subproblems of the same type.
// Each subproblem is solved by applying the same algorithm recursively until a base case is reached,
// at which point the recursion stops. Here's a simple example of a recursive algorithm in C++ to calculate the factorial of a number:

//In this example, the factorial function is defined recursively. It calculates the factorial of a number n by first checking if n is a base case (0 or 1),
// in which case the factorial is 1. If n is not a base case, it recursively calls itself with n-1 and multiplies the result by n.
// This process continues until the base case is reached.

//Remember that when working with recursive algorithms, it's essential to have a termination condition (base case) to avoid infinite recursion.

// Recursive function to calculate the factorial of a number
unsigned long long factorial(int n) {
    // Base case: If n is 0 or 1, the factorial is 1
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case: n! = n * (n-1)!
    return n * factorial(n - 1);
}

int main() {
    int num;
    std::cout << "Enter a non-negative integer: ";
    std::cin >> num;

    if (num < 0) {
        std::cout << "Factorial is not defined for negative numbers." << std::endl;
    } else {
        unsigned long long result = factorial(num);
        std::cout << "Factorial of " << num << " is " << result << std::endl;
    }

    return 0;
}