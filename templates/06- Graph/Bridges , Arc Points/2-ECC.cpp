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

