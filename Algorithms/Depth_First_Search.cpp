#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
using namespace std;

 
struct Graph
{
    map<int, bool> visited;
    map<int, list<int> > adj;
 
    // Function to add an edge to graph
    void addEdge(int v, int w){
      // Add w to v’s list.
      adj[v].push_back(w);
    }
 
    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v){
      // Mark the current node as visited and
      // print it
      visited[v] = true;
      cout << v << " ";
   
      // Recur for all the vertices adjacent
      // to this vertex
      list<int>::iterator i;
      for (i = adj[v].begin(); i != adj[v].end(); ++i)
          if (!visited[*i])
              DFS(*i);
    }


    bool DFS(int v, int destination, vector<int>& path) {
        path.push_back(v); // Add current node to path

        if (v == destination) {
            cout << "Path found: ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << endl;
            return true;
        }

        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (DFS(neighbor, destination, path)) {
                    return true; // Stop once destination is found
                }
            }
        }

        // Backtrack: Remove last element if path is not found
        path.pop_back();
        return false;
    }
};


struct CitiesMapGraph
{
    unordered_map<string, vector<pair<string, int>>> adj;

    // Function to add an edge with a distance (weight)
    void addEdge(const string& city1, const string& city2, int distance) {
        adj[city1].push_back({city2, distance});
        adj[city2].push_back({city1, distance}); // Assuming an undirected graph
    }

    bool DFS(const string& current, const string& destination, unordered_map<string, bool>& visited,
             vector<string>& path, int currentDistance, int& finalDistance) {
        path.push_back(current);
        visited[current] = true;

        if (current == destination) {
            finalDistance = currentDistance;
            cout << "Path found: ";
            for (const string& city : path) {
                cout << city << " -> ";
            }
            cout << "Total Distance: " << finalDistance << " km\n";
            return true;
        }

        for (auto& [neighbor, distance] : adj[current]) {
            if (!visited[neighbor]) {
                if (DFS(neighbor, destination, visited, path, currentDistance + distance, finalDistance)) {
                    return true; // Stop searching when the destination is found
                }
            }
        }

        // Backtrack
        path.pop_back();
        return false;
    }
};

int main()
{
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
 
    /*g.DFS(2);*/
    vector<int> path1;
    g.DFS(0,3,path1);

    CitiesMapGraph cities_g;
    cities_g.addEdge("New York", "Los Angeles", 4500);
    cities_g.addEdge("New York", "Chicago", 1200);
    cities_g.addEdge("Chicago", "Denver", 1600);
    cities_g.addEdge("Denver", "San Francisco", 1900);
    cities_g.addEdge("Los Angeles", "San Francisco", 600);
    cities_g.addEdge("Chicago", "Los Angeles", 2800);

    unordered_map<string, bool> visited;
    vector<string> path2;
    int finalDistance = 0;

    if (!cities_g.DFS("New York", "Denver", visited, path2, 0, finalDistance)) {
        cout << "No path found.\n";
    }

}
