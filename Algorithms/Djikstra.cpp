#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void Dijkstra(vector<vector<pair<int, int>>>& graph, vector<int>& d, vector<int>& predecessor, int source) {
    int n = graph.size();

    // Inicjalizacja tablic d i poprzedników
    for (int v = 0; v < n; ++v) {
        d[v] = INF;
        predecessor[v] = -1;
    }

    d[source] = 0;

    // Kolejka priorytetowa (waga, wierzchołek)
    set<pair<int, int>> Q;
    for (int v = 0; v < n; ++v) {
        Q.insert({d[v], v});
    }

    while (!Q.empty()) {
        int u = Q.begin()->second; // Zdejmij wierzchołek o najmniejszym koszcie
        Q.erase(Q.begin());

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Relaksacja krawędzi
            if (d[v] > d[u] + weight) {
                Q.erase({d[v], v}); // Aktualizacja kolejki priorytetowej
                d[v] = d[u] + weight;
                predecessor[v] = u;
                Q.insert({d[v], v});
            }
        }
    }
}

int main() {
    // Przykładowy graf skierowany z wagami (u, v, waga)
    vector<vector<pair<int, int>>> graph = {
        {{1, 5}, {2, 1}},
        {{3, 2}},
        {{1, 9}, {3, 6}},
        {{4, 3}},
        {},
    };

    int source = 0; // Wierzchołek źródłowy

    int n = graph.size();
    vector<int> distance(n, INF); // Koszt dojścia do każdego wierzchołka
    vector<int> predecessor(n, -1); // Poprzednicy na najkrótszej ścieżce do każdego wierzchołka

    Dijkstra(graph, distance, predecessor, source);

    // Wyświetlenie wyniku (najkrótsze ścieżki do wszystkich wierzchołków)
    for (int v = 0; v < n; ++v) {
        cout << "Najkrotsza sciezka do wierzcholka " << v << ": ";
        if (distance[v] == INF) {
            cout << "Brak sciezki" << endl;
        } else {
            // Odtworzenie ścieżki
            vector<int> path;
            for (int current = v; current != -1; current = predecessor[current]) {
                path.push_back(current);
            }

            // Wyświetlenie ścieżki
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i];
                if (i > 0) cout << " -> ";
            }
            cout << " (Koszt: " << distance[v] << ")" << endl;
        }
    }

    std::cin.get();
}
