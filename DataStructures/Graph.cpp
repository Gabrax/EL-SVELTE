#include <iostream>
#include <vector>

//In C++, you can represent a graph data structure using various techniques and data structures.
// The choice of representation depends on the specific requirements of your application.

//Adjacency Matrix:
//An adjacency matrix is a 2D array where each element (i, j) represents an edge between vertex i and vertex j.
// It is suitable for dense graphs but can be memory-intensive for large graphs.

const int MAX_VERTICES = 100;
int graph[MAX_VERTICES][MAX_VERTICES] = {0};

//Adjacency List:
//An adjacency list is a collection of lists or arrays where each vertex has a list of its neighboring vertices.
// It is suitable for sparse graphs and is memory-efficient.
std::vector<int> adjList[MAX_VERTICES];

//Edge List:
//An edge list is a simple list of edges, each represented by a pair of vertices.
// It is useful for algorithms like Kruskal's Minimum Spanning Tree algorithm.

struct Edge {
    int src, dest;
};

std::vector<Edge> edgeList;

//Graph Class:
//You can create a custom class to represent a graph with methods for adding vertices and edges,
// and possibly other graph-related operations.

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
};

Graph::Graph(int vertices) {
    V = vertices;
    adj.resize(V);
}

void Graph::addEdge(int src, int dest) {
    adj[src].push_back(dest);
    adj[dest].push_back(src); // Uncomment for undirected graphs
}
