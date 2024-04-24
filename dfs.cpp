#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

// Function to add an edge to the adjacency list
void addEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);  // For undirected graph, add both directions
}

// Function to perform sequential DFS
void sequentialDFS(vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    // Initialize a stack for DFS
    stack<int> s;
    s.push(start);
    visited[start] = true;

    // Start timer
    double start_time = omp_get_wtime();

    // While the stack is not empty
    while (!s.empty()) {
        // Pop the top node from the stack
        int node = s.top();
        s.pop();

        // Process the node

        // Sequentially process the unvisited neighbors
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                // Mark the neighbor as visited and push it onto the stack
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }

    // End timer
    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    cout << "Sequential DFS Execution Time: " << duration << " seconds" << endl;
}

// Function to perform parallel DFS
void parallelDFS(vector<vector<int>>& graph, int start) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    // Initialize a stack for DFS
    stack<int> s;
    s.push(start);
    visited[start] = true;

    // Start timer
    double start_time = omp_get_wtime();

    // While the stack is not empty
    while (!s.empty()) {
        // Pop the top node from the stack
        int node = s.top();
        s.pop();

        // Process the node

        // Parallelize the processing of unvisited neighbors
        #pragma omp parallel for
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                // Mark the neighbor as visited and push it onto the stack
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }

    // End timer
    double end_time = omp_get_wtime();
    double duration = end_time - start_time;

    cout << "Parallel DFS Execution Time: " << duration << " seconds" << endl;
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

    // Perform sequential DFS from node 0
    sequentialDFS(graph, 0);

    // Perform parallel DFS from node 0
    parallelDFS(graph, 0);

    return 0;
}
