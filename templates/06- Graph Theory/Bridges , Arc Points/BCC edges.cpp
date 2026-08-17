// Important BCC application:
//
// Every simple cycle lies completely inside one BCC.
//
// For each BCC:
//      E = number of edges
//      V = number of distinct vertices
//
// if(E == V)
//      BCC is exactly one simple cycle.
struct Biconnected {
    int n, timer;
    vector<vector<pair<int,int>>> adj; // {to, edge_id}
    vector<pair<int,int>> edges;       // edges[id] = {u,v}

    vector<int> tin, low;
    vector<bool> is_cutpoint;

    vector<vector<int>> BCC; // edge IDs inside each BCC
    vector<int> st;          // edge stack

    // Block-Cut Tree
    vector<vector<int>> tree;
    vector<int> id;          // original vertex -> BCT node
    int bct_n;

    Biconnected(int n, vector<pair<int,int>> &ed) : n(n), edges(ed) {
        int m = edges.size();

        adj.assign(n, {});
        for(int i = 0; i < m; i++) {
            auto [u,v] = edges[i];
            adj[u].push_back({v,i});
            adj[v].push_back({u,i});
        }

        tin.assign(n, 0);
        low.assign(n, 0);
        is_cutpoint.assign(n, false);
        id.assign(n, -1);
        timer = 0;

        // Find articulation points + edge-BCCs
        for(int i = 0; i < n; i++) {
            if(!tin[i])
                dfs(i, -1);
        }

        build_tree();
    }

    void dfs(int u, int parent_edge) {
        tin[u] = low[u] = ++timer;
        int children = 0;

        for(auto [v, eid] : adj[u]) {
            if(eid == parent_edge) continue;

            if(!tin[v]) {
                children++;
                st.push_back(eid);

                dfs(v, eid);

                low[u] = min(low[u], low[v]);

                if(low[v] >= tin[u]) {
                    if(parent_edge != -1)
                        is_cutpoint[u] = true;

                    vector<int> comp;

                    while(true) {
                        int e = st.back();
                        st.pop_back();

                        comp.push_back(e);

                        if(e == eid) break;
                    }

                    BCC.push_back(comp);
                }
            }
            else if(tin[v] < tin[u]) {
                // back edge to ancestor
                st.push_back(eid);
                low[u] = min(low[u], tin[v]);
            }
        }

        if(parent_edge == -1 && children > 1)
            is_cutpoint[u] = true;
    }

    void build_tree() {
        // 0..n-1 reserved for articulation vertices
        tree.resize(n + BCC.size());
        bct_n = n;

        for(auto &comp : BCC) {
            int block = bct_n++;

            vector<int> vertices;

            for(int eid : comp) {
                auto [u,v] = edges[eid];
                vertices.push_back(u);
                vertices.push_back(v);
            }

            sort(vertices.begin(), vertices.end());
            vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

            for(int u : vertices) {
                if(is_cutpoint[u]) {
                    tree[u].push_back(block);
                    tree[block].push_back(u);
                    id[u] = u;
                }
                else {
                    id[u] = block;
                }
            }
        }

        // isolated vertices
        for(int u = 0; u < n; u++) {
            if(id[u] == -1) {
                int block = bct_n++;
                tree.push_back({});
                id[u] = block;
            }
        }
    }
};
