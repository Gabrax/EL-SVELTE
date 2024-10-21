#include <iostream>

// Function to compute Euler's totient function φ(k) for a given k
int eulerTotient(int k) {
    int result = k;
    for (int i = 2; i * i <= k; i++) {
        if (k % i == 0) {
            while (k % i == 0) {
                k /= i;
            }
            result -= result / i;
        }
    }
    if (k > 1) {
        result -= result / k;
    }
    return result;
}

// Function to check if the formula holds for a given n
bool checkFormula(int n) {
    int sum = 0;
    // Sum φ(k) for all divisors k of n
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {  // Check if k is a divisor of n
            sum += eulerTotient(i);
        }
    }
    return sum == n;
}

int main() {
    for (int n = 1; n <= 1000; n++) {
        if (!checkFormula(n)) {
            std::cout << "The formula does not hold for n = " << n;
        }
    }

    std::cout << "The formula holds for all n from 1 to 1000.";
}
