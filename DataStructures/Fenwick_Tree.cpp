#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
private:
    vector<int> bit; // Binary Indexed Tree
    int n;

public:
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0); // 1-based index
    }

    // Add value to index i
    void update(int i, int delta) {
        while (i <= n) {
            bit[i] += delta;
            i += (i & -i); // Move to the next responsible index
        }
    }

    // Query sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= (i & -i); // Move to parent index
        }
        return sum;
    }

    // Get sum of range [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    int n = 10; // Size of the array
    FenwickTree fenwick(n);

    // Sample updates
    fenwick.update(1, 5);
    fenwick.update(3, 7);
    fenwick.update(4, 6);
    fenwick.update(7, 2);

    // Sample queries
    cout << "Sum of first 5 elements: " << fenwick.query(5) << endl;
    cout << "Sum of range [2, 7]: " << fenwick.rangeQuery(2, 7) << endl;
}
