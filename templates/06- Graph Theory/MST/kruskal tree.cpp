/**
 * ==================================================================================
 * KRUSKAL RECONSTRUCTION TREE (DSU TREE / REACHABILITY TREE)
 * ==================================================================================
 * * WHAT IT IS:
 * A tree built during Kruskal's algorithm. Instead of just setting parent[u] = v,
 * we create a NEW virtual node 'new_root' representing the edge (u, v) and make
 * it the parent of the roots of the components of u and v.
 * * * PROPERTIES:
 * 1. Structure: It is a rooted binary tree with at most 2*N - 1 nodes.
 * - Leaves (0..N-1): The original graph nodes.
 * - Internal Nodes (N..2N-2): Represent the edges/merges.
 * 2. Heap Property: If edges are sorted by weight ascendingly, the weights of nodes
 * increase as you go up the tree. Root has the max weight.
 * 3. LCA Property: The weight of LCA(u, v) is the Minimum Maximum Edge weight
 * (Bottleneck) on the path between u and v in the original graph.
 * * * COMMON USES:
 * 1. Minimax Path Query: Query max weight on path u->v in O(log N) using LCA.
 * -> ans = val[lca(u, v)]
 * 2. Reachability: Count nodes reachable from 'u' using edges <= W.
 * -> Lift 'u' up to the highest ancestor with weight <= W. Return subtree size.
 * * * CONSTRUCTION COMPLEXITY: O(M log M) (due to sorting edges)
 * * SPACE COMPLEXITY: O(N)
 * ==================================================================================
 */

struct KruskalTree {
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const { return w < other.w; }
    };

    int n;              // Number of original nodes
    int total_nodes;    // Total nodes (leaves + virtual)
    int root;           // Root of the DSU tree
    
    // DSU state
    vector<int> par;
    
    // Tree state
    vector<vector<int>> adj; // Adjacency list of the tree
    vector<int> val;         // Weight of the node
    
    KruskalTree(int _n) : n(_n) {
        total_nodes = n; // Starts with n leaves
        par.resize(2 * n);
        iota(all(par), 0);
        adj.resize(2 * n);
        val.resize(2 * n, 0); 
    }

    int find(int i) {
        if (par[i] == i) return i;
        return par[i] = find(par[i]);
    }

    // Input: List of edges {u, v, w}
    // Returns: The root of the tree
    int build(vector<Edge>& edges) {
        sort(all(edges));
        
        int virtual_node = n;
        for (auto& e : edges) {
            int u = find(e.u);
            int v = find(e.v);
            
            if (u != v) {
                // Create new virtual node
                val[virtual_node] = e.w;
                
                // Link in Tree (Virtual node becomes parent)
                adj[virtual_node].push_back(u);
                adj[virtual_node].push_back(v);
                
                // Link in DSU
                par[u] = par[v] = virtual_node;
                par[virtual_node] = virtual_node; // Self loop for root
                
                virtual_node++;
            }
        }
        total_nodes = virtual_node;
        root = total_nodes - 1;
        return root;
    }
};

