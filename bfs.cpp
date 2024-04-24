#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Function to add an edge to the adjacency list
void addEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);  // For undirected graph, add both directions
}

// Function to perform sequential BFS
void sequentialBFS(vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    // Initialize a queue for BFS
    queue<int> q;
    q.push(start);
    visited[start] = true;

    // Start timer
    double start_time = omp_get_wtime();

    // While the queue is not empty
    while (!q.empty()) {
        // Dequeue a node from the queue
        int node = q.front();
        q.pop();

        // Process the node

        // Sequentially process unvisited neighbors
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                // Mark the neighbor as visited and enqueue it
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // End timer
    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    cout << "Sequential BFS Execution Time: " << duration << " seconds" << endl;
}

// Function to perform parallel BFS
void parallelBFS(vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    // Initialize a queue for BFS
    queue<int> q;
    q.push(start);
    visited[start] = true;

    // Start timer
    double start_time = omp_get_wtime();

    // While the queue is not empty
    while (!q.empty()) {
        // Number of elements in the queue at this level
        int levelSize = q.size();

        // Parallelize the processing of nodes at this level
        #pragma omp parallel for
        for (int i = 0; i < levelSize; ++i) {
            // Dequeue a node from the queue
            int node = q.front();
            q.pop();

            // Process the node

            // Enqueue unvisited neighbors
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // End timer
    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    cout << "Parallel BFS Execution Time: " << duration << " seconds" << endl;
}

int main() {
    // Number of nodes in the graph
    int numNodes = 6;
    // Example graph represented as an adjacency list
    vector<vector<int>> graph(numNodes);

    // Adding edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    // Perform sequential BFS from node 0
    sequentialBFS(graph, 0);

    // Perform parallel BFS from node 0
    parallelBFS(graph, 0);

    return 0;
}
