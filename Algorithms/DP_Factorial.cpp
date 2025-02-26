#include <iostream>
#include <vector>


unsigned long long Memoizationfactorial(int n) {
    // Memoization array (initialized with -1)
    std::vector<unsigned long long> memo(100, -1);
    // Base case
    if (n == 0 || n == 1) {
        return 1;
    }
    
    // If already computed, return the stored result
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // Compute and store the result
    return memo[n] = n * Memoizationfactorial(n - 1);
}

unsigned long long Tabulationfactorial(int n) {
    std::vector<unsigned long long> dp(n + 1, 1); // Initialize Tabulation array

    for (int i = 2; i <= n; i++) {
        dp[i] = i * dp[i - 1]; // Compute iteratively
    }

    return dp[n];
}

int main() {

  std::cout << Tabulationfactorial(20);
}

