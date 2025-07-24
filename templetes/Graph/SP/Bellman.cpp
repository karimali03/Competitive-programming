const int OO = 1e17;

struct edge {
        int from, to, w;
        edge(int from=0, int to=0, int w=0) :
        from(from), to(to), w(w) {
        }
};

pair<bool,vector<int>> BellmanFord(vector<edge> &edgeList, int n, int src) {
        vector<int> dist(n, OO);
        bool neg_cycle = false;
        dist[src] = 0;
        vector<int>par(n,-1);
        int x = -1;
        for (int it = 0; it < n ; ++it) {
            bool any_updates = false;
            for (int j = 0; j < (int) edgeList.size(); ++j) {
                edge &ne = edgeList[j];	
                if (dist[ne.to] > dist[ne.from] + ne.w) {
                    dist[ne.to] = dist[ne.from] + ne.w;
                    par[ne.to] = ne.from;
                    x = ne.to;
                    // at nth iteration {from,to} is part of neg cycle or in a path towards neg cycle
                    any_updates = true;
                }
            }
            if(!any_updates) break;
            if(it == n-1) neg_cycle = true;   
        }

        // return {neg_cycle ,dist}
        // find a neg cycle
        if(!neg_cycle) return {false,{}};
        vi path;
        for (int i = 0; i < n; ++i)  x = par[x];
        // to gurantee be in the cycle
        for(int v = x ; ; v = par[v]){
            path.push_back(v);
            if(v == x && path.size() > 1) break;
        }
        reverse(all(path));
        return {true,path};
}
