/*
Edge Classification During DFS:

For a directed graph, DFS classifies each edge (u, v) into one of the following types:
1. Tree Edge: v is visited for the first time during DFS(u) — it's part of the DFS tree.
2. Back Edge: v is an ancestor of u (entry[v] < entry[u] and v is not exited yet) — indicates a cycle.
3. Forward Edge: v is a descendant of u (entry[u] < entry[v] and v already exited).
4. Cross Edge: v is neither ancestor nor descendant (entry[v] < entry[u] and v already exited).

For an **undirected graph**, only:
- Tree Edges and 
- Back Edges 

Edge Classification in DFS (for Directed Graphs):

During DFS, each edge (u → v) is classified based on the state and timing of discovery of v:

1. Tree Edge:
   - v is unvisited when (u → v) is explored.
   - Represents traversal to a new node.
   - Forms the DFS tree.

2. Back Edge:
   - v is an ancestor of u.
   - entry[v] < entry[u] && v is not yet exited.
   - Indicates a cycle in the graph.

3. Forward Edge:
   - v is a descendant of u, but already fully visited.
   - entry[u] < entry[v] && exit[v] < exit[u].

4. Cross Edge:
   - v is neither ancestor nor descendant of u.
   - entry[v] < entry[u] && exit[v] < exit[u].
   - Connects nodes in different branches or subtrees.

Note (Undirected Graphs):
- Only Tree and Back edges occur.
- Forward and Cross edges don’t exist due to bidirectional nature of edges and one-time processing.

Use entry[] and exit[] timestamps from DFS to classify edges.
*/



vector<vector<int>> adj; // graph represented as an adjacency list
int n; // number of vertices
vector<int> color;

vector<int> time_in, time_out;
int dfs_timer = 0;

void dfs(int v) {
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (int u : adj[v])
        if (color[u] == 0)
            dfs(u);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}
