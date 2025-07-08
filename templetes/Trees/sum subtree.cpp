const int N = 200005;
int dp1[N],cnt[N],dp2[N];
vector<pair<int,int>>adj[N];
int n;
void rec(int u,int p){
    cnt[u] = 1;
    dp1[u] = 0;
    for(auto [it,w] : adj[u]){
        if(it == p) continue;
        rec(it,u);
        dp1[u] += w * cnt[it] + dp1[it];
        cnt[u]+=cnt[it];
    }
}

void rec2(int u, int p) {
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dp2[v] = dp2[u] + dp1[u] - (dp1[v] + cnt[v] * w) + (n - cnt[v]) * w;

        rec2(v, u);
    }
}
void init(){
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        dp1[i] = dp2[i] = cnt[i] = 0;
    }
}
