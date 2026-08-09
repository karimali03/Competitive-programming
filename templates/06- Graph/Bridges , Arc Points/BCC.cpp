/*
    ================= BICONNECTED COMPONENTS / BLOCK-CUT TREE =================

    This is the VERTEX version of bridge-tree decomposition.

    Edge failure:
        bridges -> 2-edge-connected components -> Bridge Tree

    Vertex failure:
        articulation points -> biconnected components -> Block-Cut Tree


    ================= WHEN TO USE =================

    Use this for an UNDIRECTED graph when the problem involves:

        - articulation / cut vertices
        - removing ONE vertex
        - vertices that must appear on every u -> v path
        - connectivity after vertex failure
        - biconnected components (BCC)
        - compressing graph around articulation points
        - path queries involving unavoidable vertices


    ================= CORE IDEA =================

    A BCC is a maximal part of the graph where no single
    internal vertex removal disconnects that part.

    Example:

        triangle ----- x ----- triangle
                      ^
                 articulation

    BCCs overlap at articulation points!

        BCC1 = {a,b,x}
        BCC2 = {x,c,d}

    Unlike 2-ECC:
        every normal vertex belongs to one BCC,
        but an articulation point can belong to MULTIPLE BCCs.

    Because of this, we cannot simply compress every BCC
    into one node like the bridge tree.


    ================= BLOCK-CUT TREE =================

    Create two kinds of nodes:

        1) Articulation nodes
        2) BCC / block nodes

    Connect:

        articulation x ---- block B

    iff x belongs to B.

    Example:

        BCC1 -- x -- BCC2 -- y -- BCC3

    This graph is a TREE (or forest if original graph is disconnected).


    ================= OUTPUT OF THIS TEMPLATE =================

    ArticPoints ap(n, g);

    ap.is_cutpoint[v]
        -> true if v is an articulation point


    ap.BCC
        -> list of biconnected components

        for(auto &comp : ap.BCC) {
            for(int v : comp) {
                ...
            }
        }


    ap.tree
        -> Block-Cut Tree


    ap.id[v]
        -> where original vertex v lives in the Block-Cut Tree

        if v is NOT articulation:
            id[v] = its BCC/block node

        if v IS articulation:
            id[v] = v


    ================= LOW-LINK RULE =================

    For DFS tree edge:

        u -> v

    if:

        low[v] >= in[u]

    then v's subtree cannot reach an ancestor of u
    without passing through u.

    Therefore u separates this BCC.

    Compare:

        low[v] >  in[u]  => edge (u,v) is a BRIDGE

        low[v] >= in[u]  => u is a BCC boundary /
                             possible ARTICULATION POINT


    ROOT SPECIAL CASE:

        DFS root is articulation iff it has >= 2 DFS children.


    ================= COMMON USAGE =================

    1) Is v an articulation point?

        if(ap.is_cutpoint[v]) ...


    2) Connectivity after removing one vertex

        Think:
            articulation points
                ->
            Block-Cut Tree


    3) Which vertices are unavoidable between u and v?

        Convert:

            u -> ap.id[u]
            v -> ap.id[v]

        Then look at the path between them in the Block-Cut Tree.

        Articulation nodes on this path are the vertices
        that separate u and v.


    4) Number of articulation points separating u and v

        Block-Cut Tree
            +
        LCA / prefix sums

        Give articulation-node weight = 1,
        block-node weight = 0,
        then query path sum.


    5) Many connectivity queries involving vertex deletion

        Original graph can be complicated.

        Compress into Block-Cut Tree
            ->
        solve tree path / subtree queries.


    ================= MEMORY TRIGGER =================

    If statement says:

        "remove one VERTEX"
        "cut vertex"
        "articulation point"
        "vertex that every path must pass through"
        "remain connected after vertex failure"

    THINK:

        ARTICULATION POINT
               ↓
              BCC
               ↓
         BLOCK-CUT TREE
               ↓
         TREE ALGORITHM


    VERY IMPORTANT COMPARISON:

        EDGE problem:
            Bridge Tree

        VERTEX problem:
            Block-Cut Tree
*/
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
