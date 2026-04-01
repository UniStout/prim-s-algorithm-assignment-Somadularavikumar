#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Prim's Algorithm using adjacency matrix
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V, -1);   // Stores the MST
    vector<int> key(V, INT_MAX); // Min weight to include each vertex
    vector<bool> inMST(V, false);

    key[0] = 0; // Start from vertex 0

    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex not yet in MST
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;

        inMST[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the MST
    int totalWeight = 0;
    cout << "Edge\tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[parent[i]][i] << "\n";
        totalWeight += graph[parent[i]][i];
    }
    cout << "Total MST Weight: " << totalWeight << "\n";
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error: could not open input.txt\n";
        return 1;
    }

    int V, E;
    fin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < E; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // Undirected graph
    }

    fin.close();

    primMST(graph, V);

    return 0;
}
