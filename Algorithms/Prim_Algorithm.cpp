// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
 
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>

typedef std::pair<int, int> iPair;  // Definicja pary typu (waga, wierzchołek)

void printMST(const std::vector<int>& parent, const std::vector<std::vector<int>>& graph, int V) {
    std::cout << "Krawedz\tWaga\n";
    for (int i = 1; i < V; i++) {
        std::cout << parent[i] << " - " << i << '\t' << graph[i][parent[i]] << '\n';
    }
}

void PrimAlgo(const std::vector<std::vector<int>>& graph, int V) {
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;  // Kopiec minimalny

    int src = 0;  // Startujemy od wierzchołka 0

    std::vector<int> key(V, std::numeric_limits<int>::max());  // Wartości klucza dla wierzchołków
    std::vector<int> parent(V, -1);  // Tablica rodziców MST
    std::vector<bool> inMST(V, false);  // Czy wierzchołek jest w MST

    pq.push(std::make_pair(0, src));  // Dodanie źródła do kopca
    key[src] = 0;  // Wartość klucza źródła ustawiona na 0

    while (!pq.empty()) {
        int u = pq.top().second;  // Pobranie wierzchołka o najmniejszej wartości klucza
        pq.pop();

        inMST[u] = true;  // Dodanie wierzchołka do MST

        // Przeszukiwanie wszystkich sąsiadów wierzchołka u
        for (int v = 0; v < V; v++) {
            int weight = graph[u][v];  // Waga krawędzi u-v

            if (weight && !inMST[v] && weight < key[v]) {  // Aktualizacja klucza, jeśli waga jest mniejsza
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;  // Ustawienie rodzica wierzchołka v
            }
        }
    }

    printMST(parent, graph, V);  // Drukowanie wyniku
}

int main() {
    int V;
    std::cout << "Liczba wierzcholkow: ";
    std::cin >> V;

    std::vector<std::vector<int>> graph(V, std::vector<int>(V));  // Inicjalizacja macierzy sąsiedztwa

    std::cout << "Macierz sasiedztwa:" << '\n';
    for (int i = 0; i < V; i++) {  // Wczytanie macierzy sąsiedztwa
        for (int j = 0; j < V; j++) {
            std::cin >> graph[i][j];
        }
    }

    PrimAlgo(graph, V);  // Wywołanie algorytmu Prima
}

/* graf 1
   0 2 0 6 0
   2 0 3 8 5
   0 3 0 0 7
   6 8 0 0 9    
   0 5 7 9 0
*/

/* graf 2
    0 4 0 6 0 0
    4 0 7 0 11 0
    0 7 0 0 0 4
    6 0 0 0 2 0
    0 11 0 2 0 1
    0 0 4 0 1 0
*/
