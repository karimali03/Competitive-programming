struct Edge{
    int to;
    ll w;
};
const ll INF = (1LL << 62);
struct SegTreeGraph{
    int n;
    int nodes;
    vector<int> in,out;
    vector<vector<Edge>>g;
    SegTreeGraph(int n):n(n){
        nodes = n;
        // add 2*m if range to range
        int max_nodes = 3*n+5;
        in.resize(4 * n + 5);
        out.resize(4 * n + 5);
        g.resize(max_nodes);
        build(1,1,n);
    }
    void add(int from,int to,ll w){
        g[from].push_back({to,w});
    }
    void build(int p,int l,int r){
        if(l == r){
            in[p] = out[p] = l; return;
        }
        int mid = (l+r) >> 1;
        build(p*2,l,mid);
        build(p*2+1,mid+1,r);
        in[p] = ++nodes;
        out[p] = ++nodes;
        // out  parent -> childs
        add(out[p],out[p*2],0); add(out[p],out[p*2+1],0);
        // in parent <- childs
        add(in[p*2],in[p],0); add(in[p*2+1],in[p],0);
    }

    void NodeToRange(int u,int ql,int qr,ll w,int p,int l,int r){
        if(ql <= l && qr >= r){
            add(u,out[p],w);
            return;
        }
        int mid = (l+r) >> 1;
        if(ql <= mid){
            NodeToRange(u,ql,qr,w,p*2,l,mid);
        }
        if(qr > mid){
            NodeToRange(u,ql,qr,w,p*2+1,mid+1,r);
        }
    }
    void NodeToRange(int u,int ql,int qr,ll w){
        NodeToRange(u,ql,qr,w,1,1,n);
    }
    void RangeToNode(int u,int ql,int qr,ll w,int p,int l,int r){
        if(ql <= l && qr >= r){
            add(in[p],u,w);
            return;
        }
        int mid = (l+r) >> 1;
        if(ql <= mid){
            RangeToNode(u,ql,qr,w,p*2,l,mid);
        }
        if(qr > mid){
            RangeToNode(u,ql,qr,w,p*2+1,mid+1,r);
        }
    }
    void RangeToNode(int u,int ql,int qr,ll w){
        RangeToNode(u,ql,qr,w,1,1,n);
    }

    void RangeToRange(int l1,int r1,int l2,int r2,ll w){
        int aux = ++nodes;
        RangeToNode(aux,l1,r1,w);
        NodeToRange(aux,l2,r2,0);
    }
    vector<ll> Dikstra(int u){
        vector<ll> dist(nodes+1,INF);
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>q;
        q.push({0,u}); dist[u] = 0;
        while(!q.empty()){
            auto [d,v] = q.top(); q.pop();
            if(d != dist[v]) continue;
            for(auto ch : g[v]){
                int to = ch.to;
                ll w = ch.w;
                if(dist[to] > w + dist[v]){
                    dist[to] = w + dist[v];
                    q.push({dist[to],to});
                }
            }
        }
        return dist;
    }

};
