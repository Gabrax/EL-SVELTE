#include <iostream>

//A brute force algorithm is a straightforward approach to solving a problem by systematically trying all possible solutions.
// It is not always the most efficient way to solve a problem,
// but it can be useful for small input sizes or when more optimized algorithms are not readily available or necessary.

//In this example, we have defined a function bruteForceFactorial that calculates the factorial of a non-negative integer n using a brute force approach.
// It iterates from 2 to n, multiplying the current result by each number in the range.



// Function to calculate the factorial of a number using brute force
unsigned long long bruteForceFactorial(int n) {
    if (n < 0) {
        // Factorial is undefined for negative numbers
        return 0;
    }

    if (n == 0 || n == 1) {
        // 0! and 1! are both equal to 1
        return 1;
    }

    unsigned long long result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

int main() {
    int n;
    std::cout << "Enter a non-negative integer: ";
    std::cin >> n;

    unsigned long long factorial = bruteForceFactorial(n);

    std::cout << n << "! = " << factorial << std::endl;

    return 0;
}
