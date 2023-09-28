#include <iostream>
#include <queue>
#include <vector>

//a queue is a linear data structure that follows the First-In-First-Out (FIFO) principle,
// meaning that the element that is added first will be the one removed first.
// C++ provides a built-in queue data structure as part of the Standard Template Library (STL).

int main()
{
    //Declare a queue:
    std::queue<int> myQueue;
    //Operations on a Queue:
    //Push: Add an element to the back of the queue.
    myQueue.push(value);
    //Pop: Remove the front element of the queue.
    myQueue.pop();
    //Front: Access the front element of the queue.
    int frontElement = myQueue.front();
    //Back: Access the back element of the queue.
    int backElement = myQueue.back();
    //Size: Get the number of elements in the queue.
    int queueSize = myQueue.size();
    //Empty: Check if the queue is empty.
    bool isEmpty = myQueue.empty();
}
//Here's a simple example of using a queue to perform a breadth-first search (BFS) traversal of a graph:
using namespace std;

int main() {
    vector<vector<int>> graph = {{1, 2}, {0, 3, 4}, {0, 5, 6}, {1}, {1}, {2}, {2}};
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    // Start BFS from node 0
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    cout << endl;
    return 0;
}
//In this example, we use a queue to perform BFS traversal of a graph represented as an adjacency list.
// The queue is used to process nodes in the order they were discovered, following the FIFO principle.
