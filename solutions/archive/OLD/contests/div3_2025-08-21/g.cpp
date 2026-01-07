 set<int> brid;
    vi seen2(n);
    seen2[n-1] = 1;
    function<int(int,int)> dfs = [&](int i,int p) -> int {
        if(seen2[i]) return seen2[i];
        bool ret = false;
        for(auto [a,b] : adj[i]){
            if(a == p) continue;
            dfs(a,i);
            if( (seen2[a] == 1) && is_bridge[b]) brid.insert(b);
            ret|=(seen2[a] == 1);
        }
        return seen2[i] = (ret ? 1 : 2);
    };