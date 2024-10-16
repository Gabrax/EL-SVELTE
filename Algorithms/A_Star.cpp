#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <unordered_map>

// Node structure representing a position in the grid
struct Node {
    int x, y;                       // Coordinates of the node
    float gCost, hCost, fCost;      // Cost values for A* algorithm
    Node* parent;                   // Pointer to the parent node

    // Default constructor
    Node() : x(0), y(0), parent(nullptr) {}
    
    // Constructor to initialize a node
    Node(int x, int y, Node* parent = nullptr)
        : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(parent) {}

    // Overloading equality operator to compare two nodes
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// Heuristic function using Manhattan distance
float heuristic(const Node& a, const Node& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// Function to reconstruct the path from start to goal
std::vector<Node> reconstructPath(Node* currentNode) {
    std::vector<Node> path;
    while (currentNode != nullptr) {
        path.push_back(*currentNode);           // Add the current node to the path
        currentNode = currentNode->parent;      // Move to the parent node
    }
    std::reverse(path.begin(), path.end());     // Reverse the path to get correct order
    return path;
}

// A* algorithm implementation
std::vector<Node> aStar(const std::vector<std::vector<int>>& grid, const Node& start, const Node& goal) {
    // Priority queue (min-heap) to store open nodes, sorted by fCost
    auto compare = [](const std::pair<float, Node*>& a, const std::pair<float, Node*>& b) {
        return a.first > b.first;
    };
    std::priority_queue<std::pair<float, Node*>, std::vector<std::pair<float, Node*>>, decltype(compare)> openSet(compare);

    std::unordered_map<int, Node> allNodes;  // To store all nodes for easy lookup

    Node* startNode = new Node(start.x, start.y);
    startNode->gCost = 0;
    startNode->hCost = heuristic(start, goal);
    startNode->fCost = startNode->gCost + startNode->hCost;
    openSet.push({startNode->fCost, startNode});
    allNodes[startNode->x * grid[0].size() + startNode->y] = *startNode;

    std::vector<std::vector<bool>> closedSet(grid.size(), std::vector<bool>(grid[0].size(), false));

    // Direction vectors for moving up, down, left, right
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Main loop of the A* algorithm
    while (!openSet.empty()) {
        Node* currentNode = openSet.top().second;
        openSet.pop();

        // Check if we reached the goal
        if (*currentNode == goal) {
            return reconstructPath(currentNode);
        }

        closedSet[currentNode->x][currentNode->y] = true;

        // Explore neighboring nodes
        for (auto& dir : directions) {
            int newX = currentNode->x + dir.first;
            int newY = currentNode->y + dir.second;

            // Check for valid grid position and non-obstacle
            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] == 0) {
                if (closedSet[newX][newY]) {
                    continue;  // Skip if node is already in the closed set
                }

                float tentativeGCost = currentNode->gCost + 1.0f;  // Assuming uniform cost to move to neighbor

                int nodeIndex = newX * grid[0].size() + newY;
                Node* neighbor = nullptr;

                if (allNodes.find(nodeIndex) == allNodes.end()) {
                    neighbor = new Node(newX, newY, currentNode);
                    allNodes[nodeIndex] = *neighbor;
                } else {
                    neighbor = &allNodes[nodeIndex];
                }

                // Check if this path to neighbor is better than any previous one
                if (tentativeGCost < neighbor->gCost || neighbor->gCost == 0) {
                    neighbor->gCost = tentativeGCost;
                    neighbor->hCost = heuristic(*neighbor, goal);
                    neighbor->fCost = neighbor->gCost + neighbor->hCost;
                    neighbor->parent = currentNode;

                    openSet.push({neighbor->fCost, neighbor});
                }
            }
        }
    }

    // Return an empty path if there is no solution
    return std::vector<Node>();
}

// Test function to demonstrate the A* algorithm
int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    Node start(0, 0);  // Starting position (top-left corner)
    Node goal(4, 4);   // Goal position (bottom-right corner)

    std::vector<Node> path = aStar(grid, start, goal);

    if (!path.empty()) {
        std::cout << "Path found:\n";
        for (const Node& node : path) {
            std::cout << "(" << node.x << ", " << node.y << ") ";
        }
    } else {
        std::cout << "No path found!";
    }

    return 0;
}
