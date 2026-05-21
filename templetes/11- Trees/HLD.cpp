struct HLD {
    
    vi big,sz,depth,head,in,par;
    vii g;
    void init(int x,int d){
        sz[x] = 1;
        big[x] = -1;
        depth[x] = d;
        for(auto &it : g[x]){
            if(it == par[x]) continue;
            par[it] = x;
            init(it,d+1);
            sz[x] += sz[it];
            if(big[x] == -1 || sz[it] > sz[big[x]]) big[x] = it;
        }
    };
    
    void flatten(int x,int &timer){
        in[x] = ++timer;
        if(~big[x]){
            head[big[x]] = head[x];
            flatten(big[x],timer);
        } 
        for(auto &it : g[x]){
            if(par[x] == it || it == big[x]) continue;
            head[it] = it;
            flatten(it,timer);
        }
    }

    HLD(int n,vii &g):g(g){
        big = sz = depth = in = par = head = vi(n);
        init(0,0);
        head[0] = 0;
        int timer = -1;
        flatten(0,timer);
    };
    
    
    vector<pair<int,int>> query(int x,int y){
        vector<pair<int,int>> ret;
        while(true){
            if(depth[x] > depth[y]) swap(x,y);
            if(head[x] == head[y]){
                ret.push_back({in[x],in[y]});
                return ret;
            }
            if(depth[head[x]] < depth[head[y]]) swap(x,y);
            // x will not exceed lca
            // y may exceed lca
            ret.push_back({in[head[x]] , in[x]});
            x = par[head[x]];
        }
        return ret;
    }
    pair<vector<pair<int,int>>, vector<pair<int,int>>> query_directed(int u, int v) {
        vector<pair<int,int>> uSide, vSide;
        
        // Climb up independently
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                // u is deeper, append to uSide
                uSide.push_back({in[head[u]], in[u]});
                u = par[head[u]];
            } else {
                // v is deeper, append to vSide
                vSide.push_back({in[head[v]], in[v]});
                v = par[head[v]];
            }
        }
        
        // Handle the final segment at the LCA
        if (depth[u] > depth[v]) {
            uSide.push_back({in[v], in[u]});
        } else {
            vSide.push_back({in[u], in[v]});
        }
        
        return {uSide, vSide};
    }
    
    
};
