// Edge-ID version:
//
// bridges           -> bridge edge IDs
// is_bridge[e]      -> whether edge e is a bridge
// TwoEdgeCC[c]      -> vertices inside component c
// TwoEdgeCCEdges[c] -> non-bridge edge IDs inside component c
// comp_id[v]        -> 2-ECC containing v
// tree              -> bridge tree using compact component IDs
//
// IMPORTANT:
// Skip parent EDGE, not parent vertex:
//      if(eid == parent_edge) continue;
// This correctly handles parallel edges.
struct TwoECC {
    int n, timer;

    vector<vector<pair<int,int>>> g; // {to, edge_id}
    vector<pair<int,int>> edges;     // edges[id] = {u,v}

    vector<int> tin, low;
    vector<int> org;                 // representative of component
    vector<int> comp_id;             // component index of vertex

    vector<int> bridges;             // bridge edge IDs
    vector<bool> is_bridge;

    vector<int> st;                  // vertex stack

    vector<vector<int>> TwoEdgeCC;       // vertices in each 2-ECC
    vector<vector<int>> TwoEdgeCCEdges;  // edge IDs inside each 2-ECC

    vector<vector<int>> tree;        // bridge tree using component IDs

    TwoECC(int n, vector<pair<int,int>> &ed) : n(n), edges(ed) {
        int m = edges.size();

        g.assign(n, {});
        for(int i = 0; i < m; i++) {
            auto [u,v] = edges[i];
            g[u].push_back({v,i});
            g[v].push_back({u,i});
        }

        tin.assign(n, -1);
        low.assign(n, -1);
        org.assign(n, -1);
        comp_id.assign(n, -1);
        is_bridge.assign(m, false);

        timer = 0;

        for(int i = 0; i < n; i++)
            if(tin[i] == -1)
                dfs(i, -1);

        build();
    }

    void dfs(int v, int parent_edge) {
        tin[v] = low[v] = timer++;
        st.push_back(v);

        for(auto [u, eid] : g[v]) {
            if(eid == parent_edge) continue;

            if(tin[u] != -1) {
                low[v] = min(low[v], tin[u]);
            }
            else {
                dfs(u, eid);

                low[v] = min(low[v], low[u]);

                if(low[u] > tin[v]) {
                    bridges.push_back(eid);
                    is_bridge[eid] = true;
                }
            }
        }

        if(low[v] == tin[v]) {
            vector<int> comp;
            int cid = TwoEdgeCC.size();

            while(true) {
                int u = st.back();
                st.pop_back();

                comp.push_back(u);
                comp_id[u] = cid;
                org[u] = v;

                if(u == v) break;
            }

            TwoEdgeCC.push_back(comp);
        }
    }

    void build() {
        int k = TwoEdgeCC.size();

        TwoEdgeCCEdges.assign(k, {});
        tree.assign(k, {});

        for(int eid = 0; eid < (int)edges.size(); eid++) {
            auto [u,v] = edges[eid];

            if(comp_id[u] == comp_id[v]) {
                TwoEdgeCCEdges[comp_id[u]].push_back(eid);
            }
            else {
                tree[comp_id[u]].push_back(comp_id[v]);
                tree[comp_id[v]].push_back(comp_id[u]);
            }
        }
    }
};
