struct HLD {
    
    vi big,sz,depth,head,in,par;
    vector<vector<array<int,3>>> g;
    vi val , mp;
    void init(int x,int d){
        sz[x] = 1;
        big[x] = -1;
        depth[x] = d;
        for(auto &[it,_,__] : g[x]){
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
        for(auto &[it,v,id] : g[x]){
            if(par[x] == it) continue;
            if(it != big[x]){
                head[it] = it;
                flatten(it,timer);
            }
            val[in[it]] = v;
            mp[id] = in[it];
        }
    }
    HLD(int n,vector<vector<array<int,3>>> &g):g(g){
        big = sz = depth = in = par = head = vi(n);
        val = mp = vi(n);
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
                if(in[x]+1 <= in[y]) ret.push_back({in[x]+1,in[y]});
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
    
    
};
