// Note: BFS to find shortest path solution in a game
// - States = graph vertices, transitions = edges
// - BFS ensures minimum moves in unweighted graph
// - Track visited states to avoid cycles
// - Use queue to explore states level by level
// Example: 8-puzzle
// - State: 3x3 grid configuration
// - Edge: Slide tile into empty space
// - BFS finds min moves to target configuration
// Triggers to use BFS:
// - Need minimum steps to solution
// - States/transitions form clear, unweighted graph
// - Optimal path required (e.g., solver, AI moves)



// Note: Find all vertices and edges on any shortest path (SP) between vertices a and b
// - Use BFS for shortest paths in unweighted graph
// - BFS from a: compute distances da[v] to all vertices v
// - BFS from b: compute distances db[v] to all vertices v
// - Vertex v on SP if: da[v] + db[v] == da[b] (shortest path length)
// - Edge [u,v] on SP if: da[u] + db[v] + 1 == da[b]



// Function to find the shortest cycle in a directed unweighted graph
int shortestCycle(int n, vector<vector<int>>& adj) { // O( n(n+m) )
    int minCycle = INT_MAX; // Track the shortest cycle length

    // Run BFS from each vertex
    for (int src = 0; src < n; ++src) {
        // BFS setup
        vector<int> dist(n, -1); // Distance from src to each vertex
        vector<int> parent(n, -1); // Parent for tracking path (optional)
        queue<int> q;
        
        dist[src] = 0;
        q.push(src);
        
        // BFS
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // Explore neighbors
            for (int v : adj[u]) {
                // If neighbor not visited, add to queue
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
                // If neighbor is the source vertex and not the parent,
                // we found a cycle
                else if (v == src) {
                    minCycle = min(minCycle, dist[u] + 1);
                    // No need to continue this BFS
                    break;
                }
            }
        }
    }
    
    // Return -1 if no cycle found, otherwise return shortest cycle length
    return (minCycle == INT_MAX) ? -1 : minCycle;
}





// Function to find the shortest walk of even length from s to t
int shortestEvenWalk(int n, vector<vector<int>>& adj, int s, int t) {
    // Step 1: Construct the auxiliary graph
    // Vertices are (v, c) where v is the vertex, c is parity (0 = even, 1 = odd)
    // For each vertex v, we have (v,0) and (v,1), so total vertices = 2*n
    vector<vector<int>> auxAdj(2 * n); // Adjacency list for auxiliary graph
    
    // For each edge (u,v) in original graph, add edges:
    // (u,0) -> (v,1) and (u,1) -> (v,0)
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            // From (u,0) to (v,1): even -> odd
            auxAdj[2 * u].push_back(2 * v + 1);
            // From (u,1) to (v,0): odd -> even
            auxAdj[2 * u + 1].push_back(2 * v);
        }
    }
    
    // Step 2: Run BFS on auxiliary graph from (s,0) to (t,0)
    vector<int> dist(2 * n, -1); // Distance array for auxiliary graph
    queue<int> q;
    
    // Start from (s,0) - vertex s with even length (0)
    int start = 2 * s;
    dist[start] = 0;
    q.push(start);
    
    // BFS
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : auxAdj[u]) {
            if (dist[v] == -1) { // Not visited
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    // Step 3: Return the distance to (t,0)
    int target = 2 * t; // We want to reach (t,0) - even length
    return dist[target]; // Returns -1 if unreachable, otherwise the length
}