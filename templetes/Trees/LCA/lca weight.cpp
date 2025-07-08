const int N = 200005;
int dp1[N],cnt[N],dp2[N];
vector<pair<int,int>>adj[N];
const int LOG = 17;
int up[N][LOG];
int val[N][LOG];
int lvl[N];


void init(int n){
    for (int i = 0; i < n; ++i) {
        adj[i].clear();
        lvl[i] = 0;
        for (int j = 0; j < LOG; ++j) {
            up[i][j] = 0;
            val[i][j] = 0;
        }
    }
}

int merge(int a,int b){
    return a+b;
}

void dfs(int v,int p){
    for(auto [to,w] : adj[v]){
        if(to == p) continue;
        lvl[to] = lvl[v] + 1;
        up[to][0] = v;
        val[to][0] = w;
        for(int j = 1 ; j < LOG; j++){
            up[to][j] = up[up[to][j-1]][j-1];
            val[to][j] = merge(val[to][j-1],val[up[to][j-1]][j-1]);
        }
        dfs(to,v);
    }
}   

void build(int root = 0){
    lvl[root] = 0;
    up[root][0] = root;
    val[root][0] = 0;
    for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
            val[root][j] = val[root][j-1];
    }
    dfs(root,-1);
}

int lca(int u,int v){
    if (lvl[u] < lvl[v]) swap(u, v);
    int diff = lvl[u] - lvl[v];
    for (int j = LOG - 1; j >= 0; --j)
            if ((diff >> j) & 1)  u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    return up[u][0];   
}

int get_kth(int u,int k){
     for (int j = LOG - 1; j >= 0; --j)
            if ((k >> j) & 1)  u = up[u][j];
    return u;
}

int get_dist(int u,int v){
    int lc = lca(u,v);
    int dif1 = lvl[u] - lvl[lc];
    int dif2 = lvl[v] - lvl[lc];
 
    int res = 0;
    for(int j = LOG-1 ; j >= 0 ; j--){
        if ((dif1 >> j) & 1) {
                res += val[u][j];
                u = up[u][j]; 
            }
        if ((dif2 >> j) & 1) {
                res += val[v][j];
                v = up[v][j];
        }
    }
    return res;
}

int find_node(int u,int v,int idx,int lc){
    int uc = lvl[u] - lvl[lc];
    int vc = lvl[v] - lvl[lc];
    if(idx <= uc) return get_kth(u,idx);
    return get_kth(v,vc-(idx-uc));
}

