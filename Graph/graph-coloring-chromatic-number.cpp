#include <bits/stdc++.h>
using namespace std;

// Check if it's safe to assign color c to vertex v
bool isSafe(int v, const vector<vector<int>>& adj, const vector<int>& colors, int c) {
    // Check all neighbors of the current vertex
    for (int u : adj[v]) {
        // If any neighbor has the same color we want to assign, return false
        if (colors[u] == c) {
            return false;
        }
    }
    return true;
}

// Recursive utility function for coloring
bool colorGraph(const vector<vector<int>>& adj, vector<int>& colors, int pos, int m) {
    // Base case: if all vertices are colored
    if (pos == adj.size()) {
        return true;
    }
    
    // Try different colors for current vertex
    for (int c = 1; c <= m; c++) {
        // Check if this color can be assigned
        if (isSafe(pos, adj, colors, c)) {
            // Assign the color
            colors[pos] = c;
            
            // Recur to assign colors to remaining vertices
            if (colorGraph(adj, colors, pos + 1, m)) {
                return true;
            }
            
            // If color assignment doesn't lead to a solution, backtrack
            colors[pos] = 0;
        }
    }
    
    // If no color can be assigned to this vertex
    return false;
}

// Find chromatic number of the graph
int findChromaticNumber(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> colors(n, 0);
    
    // Try with 1, 2, 3, ... n colors
    for (int m = 1; m <= n; m++) {
        // Reset color assignments
        fill(colors.begin(), colors.end(), 0);
        
        // Try coloring with m colors
        if (colorGraph(adj, colors, 0, m)) {
            // Print coloring solution
            cout << "Vertex coloring with " << m << " colors: ";
            for (int i = 0; i < n; i++) {
                cout << colors[i] << " ";
            }
            cout << endl;
            
            return m;
        }
    }
    
    // In the worst case, need as many colors as vertices
    return n;
}

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    
    // Using adjacency list representation
    vector<vector<int>> adj(n);
    
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        
        // Add edges (for undirected graph)
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Find and display the chromatic number
    int chrNum = findChromaticNumber(adj);
    cout << "Chromatic number of the graph is: " << chrNum << endl;
    
    return 0;
}