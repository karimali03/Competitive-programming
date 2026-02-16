struct ArticPoints {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> in, low;
    vector<bool> is_cutpoint;
    vector<vector<int>> BCC; // Stores nodes inside each BCC
    stack<int> st;

    // Block-Cut Tree structures
    vector<vector<int>> tree; // Adjacency list of the Block-Cut Tree
    vector<int> id;           // Maps original node -> Block-Cut Tree Node
    int bct_n;                // Total nodes in Block-Cut Tree

    ArticPoints(int _n, vector<vector<int>>& graph) {
        n = _n;
        adj = graph;
        in.assign(n, 0);
        low.assign(n, 0);
        is_cutpoint.assign(n, false);
        id.assign(n, -1);
        timer = 0;
        
        // 1. Find Articulation Points & BCCs
        for (int i = 0; i < n; ++i) {
            if (!in[i]) {
                dfs(i, -1);
                // Handle singular component (isolated node or simple edge)
                // If stack is not empty after DFS (e.g. single node), pop it
                if (!st.empty()) st.pop(); 
            }
        }

        // 2. Build Block-Cut Tree
        // Nodes 0 to n-1 in BCT are reserved for Articulation Points.
        // (We might not use all if they aren't cut points, but it simplifies mapping)
        // Nodes n, n+1, ... are for Blocks.
        
        tree.assign(n + BCC.size(), {});
        bct_n = n; // Start counter for Block nodes
        
        // Assign ID for non-cutpoints and build edges
        for (auto& comp : BCC) {
            int block_node = bct_n++; // Create a new Square Node for this Block
            
            for (int u : comp) {
                if (is_cutpoint[u]) {
                    // u is a Cut Point: connect Round Node (u) to Square Node (block_node)
                    tree[u].push_back(block_node);
                    tree[block_node].push_back(u);
                    id[u] = u; // Cut points map to themselves
                } else {
                    // u is NOT a Cut Point: it lives "inside" this block
                    id[u] = block_node; 
                }
            }
        }
    }

    void dfs(int u, int p = -1) {
        in[u] = low[u] = ++timer;
        st.push(u);
        int children = 0;

        for (int v : adj[u]) {
            if (v == p) continue;
            
            if (in[v]) {
                // Back-edge
                low[u] = min(low[u], in[v]);
            } else {
                // Tree-edge
                children++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                if (low[v] >= in[u]) {
                    // u is an Articulation Point (unless it's root with <2 kids)
                    if (p != -1) is_cutpoint[u] = true;
                    
                    // Extract the BCC (v and its descendants + u)
                    vector<int> comp;
                    comp.push_back(u); // u is part of the BCC
                    while (true) {
                        int node = st.top();
                        st.pop();
                        comp.push_back(node);
                        if (node == v) break;
                    }
                    BCC.push_back(comp);
                }
            }
        }
        
        // Root check
        if (p == -1 && children > 1) {
            is_cutpoint[u] = true;
        }
    }
};
