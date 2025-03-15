#include "dijkstras.h"

int main() {
    Graph G;
    try {
        file_to_graph("small.txt", G);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    cout << "Shortest paths from vertex " << source << ":" << endl;
    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "Path to " << i << ": ";
        print_path(path, distances[i]);
    }
    return 0;
}