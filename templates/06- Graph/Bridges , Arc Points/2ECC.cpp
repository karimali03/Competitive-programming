/*
    ==================== 2-EDGE CONNECTED COMPONENTS ====================

    Use this template for UNDIRECTED graphs when the problem involves:

    - bridges
    - removing one edge / edge failures
    - edges that MUST appear on every path
    - two edge-disjoint paths
    - compressing a graph into a tree
    - doing subtree DP / LCA / path queries between bridge-separated parts

    MAIN IDEA:
        Remove all bridges.
        The remaining connected parts are 2-edge-connected components (2-ECC).

        Compress every 2-ECC into one node:

            cyclic part --- bridge --- cyclic part --- bridge --- part

        becomes:

                 A -------- B -------- C

        This compressed graph is the BRIDGE TREE
        (bridge forest if the original graph is disconnected).


    ==================== OUTPUT OF THIS TEMPLATE ====================

    TwoECC ecc(g);

    ecc.bridges
        -> list of all bridges (u, v)

    ecc.TwoEdgeCC
        -> list of components
           each component is vector<int> of original vertices

    ecc.org[v]
        -> representative of the 2-ECC containing vertex v

        Same component:
            ecc.org[u] == ecc.org[v]

        This means no bridge separates u and v.

    ecc.tree
        -> compressed bridge tree

        IMPORTANT:
        Component IDs are representatives from the original graph,
        NOT necessarily 0,1,2,...,k-1.


    ==================== COMMON USES ====================

    1) Check if u and v are in same 2-ECC:

        if(ecc.org[u] == ecc.org[v]) {
            // no bridge separates them
            // there are 2 edge-disjoint ways between them
        }


    2) Process every bridge:

        for(auto [u, v] : ecc.bridges) {
            // u-v is a bridge
        }


    3) Solve queries about number of unavoidable edges between u and v:

        compress graph
            -> bridge tree
            -> answer distance between org[u] and org[v]
               using depth/LCA


    4) Vertex weights:

        vector<ll> compWeight(n);

        for(int v = 0; v < n; v++)
            compWeight[ecc.org[v]] += w[v];

        Then do tree DP on ecc.tree.


    5) Problem asks:
       "remove one edge and calculate something on both sides"

        Only bridges can split the graph.

        So:
            graph -> 2-ECC -> bridge tree -> subtree DP


    6) Minimum edges to add to remove all bridges:

        Usually becomes a problem about LEAVES
        of the bridge tree.


    ==================== LOW-LINK RULES ====================

    tin[v] = DFS entry time

    low[v] = smallest tin reachable from v's DFS subtree
             without using the parent edge


    For DFS edge v -> u:

        low[u] > tin[v]
            => (v,u) is a BRIDGE


    When:

        low[v] == tin[v]

    v is the root/top of one 2-ECC.
    Pop the DFS stack until v to create that component.


    ==================== IMPORTANT DETAIL ====================

    The code skips the parent only ONCE.

    This is important for parallel edges:

        v ===== u

    One edge is the DFS parent edge.
    The second edge must be treated as a back edge.

    So DON'T replace the logic with:

        if(u == p) continue;

    if multiple edges are allowed.


    ==================== MEMORY TRIGGER ====================

    If the statement says:

        "remove one edge"
        "edge must be used"
        "edge failure"
        "two edge-disjoint paths"
        "bridge"
        "add edges so graph has no bridges"

    THINK:

        BRIDGES
           ↓
        2-ECC
           ↓
        COMPRESS
           ↓
        BRIDGE TREE
           ↓
        TREE ALGORITHM

    Core takeaway:

        "If bridges are the only difficult edges,
         compress everything between bridges."
*/
struct TwoECC {
    vector<vector<int>> g;
    vector<int> low, tin, org;
    vector<pair<int,int>> bridges;
    stack<int> st;
    vector<vector<int>> TwoEdgeCC, tree;
    int timer, n;

    TwoECC(vector<vector<int>> &adj) : g(adj) {
        timer = 0;
        n = g.size();
        low = tin = org = vector<int>(n, -1);
        
        for(int i = 0; i < n; i++) {
            if(tin[i] == -1) dfs(i, -1);
        }

        // Build the Tree
        tree = vector<vector<int>>(n);
        for(int i = 0; i < n; i++) {
            for(auto &it : g[i]) {
                if(org[i] != org[it]) {
                    tree[org[i]].push_back(org[it]);
                }
            }
        }
    }

    void dfs(int v, int p) { 
        low[v] = tin[v] = timer++;
        st.push(v);
        bool skip_p = false; 
        for(auto u : g[v]) { 
            if(u == p && !skip_p) {
                skip_p = true;
                continue;
            }
            
            if(tin[u] != -1) { // back edge 
                low[v] = min(low[v], tin[u]);
            } else { // tree edge
                dfs(u, v); 
                low[v] = min(low[v], low[u]);
                if(low[u] > tin[v]) bridges.push_back({v, u});
            }
        }

        if(low[v] == tin[v]) {
            vector<int> comp;
            while(true) {
                int node = st.top();
                st.pop();
                comp.push_back(node);
                if(node == v) break;
            }
            
            int r = comp[0]; 
            for(auto &it : comp) org[it] = r;
            TwoEdgeCC.push_back(comp);
        }
    }
};

