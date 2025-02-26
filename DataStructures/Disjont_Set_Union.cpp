#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i; // Initialize each node as its own parent
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by rank
    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            if (rank[rootA] > rank[rootB]) {
                parent[rootB] = rootA;
            } else if (rank[rootA] < rank[rootB]) {
                parent[rootA] = rootB;
            } else {
                parent[rootB] = rootA;
                rank[rootA]++;
            }
        }
    }

    // Check if two elements belong to the same set
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    DSU dsu(7); // 7 elements (0 to 6)

    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(4, 5);

    cout << "Are 1 and 3 connected? " << (dsu.connected(1, 3) ? "Yes" : "No") << endl;
    cout << "Are 3 and 5 connected? " << (dsu.connected(3, 5) ? "Yes" : "No") << endl;

    dsu.unite(3, 4); // Connecting components (1-2-3) and (4-5)

    cout << "Are 3 and 5 connected after union? " << (dsu.connected(3, 5) ? "Yes" : "No") << endl;

    return 0;
}
