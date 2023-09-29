#include <iostream>
#include <vector>
#include <queue>

//Breadth-First Search (BFS) is a graph traversal algorithm that explores all the vertices of a graph in breadthward motion,
// meaning it explores all the vertices at the current level before moving on to the next level.
// It is often used to find the shortest path between two nodes in an unweighted graph or to visit all nodes in a connected component of a graph.

//in this code:
//
//We define a Graph class with methods to add edges (addEdge) and perform BFS (BFS).
//
//We maintain a visited array to keep track of visited vertices to avoid processing them more than once.
//
//We use a queue to keep track of the vertices to be processed in BFS order.
//
//The BFS function starts at a given startVertex, marks it as visited, and enqueues it.
//
//It then enters a loop where it dequeues a vertex, prints it, and enqueues its unvisited neighbors.
//
//The process continues until the queue is empty.


class Graph {
public:
    Graph(int vertices);
    void addEdge(int v, int w);
    void BFS(int startVertex);

private:
    int vertices;
    vector<vector<int>> adjacencyList;
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyList.resize(vertices);
}

void Graph::addEdge(int v, int w) {
    adjacencyList[v].push_back(w);
}

void Graph::BFS(int startVertex) {
    // Create an array to keep track of visited vertices
    vector<bool> visited(vertices, false);

    // Create a queue for BFS
    queue<int> queue;

    // Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue.front();
        cout << currentVertex << " ";
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, mark it
        // visited and enqueue it
        for (int adjacentVertex : adjacencyList[currentVertex]) {
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                queue.push(adjacentVertex);
            }
        }
    }
}

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);

    cout << "Breadth-First Traversal starting from vertex 0: ";
    g.BFS(0);

    return 0;
}