#include <iostream>
#include <vector>
#include <climits>

// Kadane's Algorithm = find the maximum subarray sum
int maxSubarraySum(const std::vector<int>& nums) {
    int maxSum = INT_MIN, currentSum = 0;

    for (int num : nums) {
        currentSum = std::max(num, currentSum + num);
        maxSum = std::max(maxSum, currentSum);
    }

    return maxSum;
}

int main() {
    std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Maximum Subarray Sum: " << maxSubarraySum(arr) << '\n';
}
