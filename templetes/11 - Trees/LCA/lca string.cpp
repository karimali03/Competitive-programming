const int P = 41;
// safe_primes = {31, 37, 41, 53, 59, 67, 71, 79, 89, 97}; 
const int M = 1e9 + 9;
const int MAXN = 1e6 + 5;
int p_pow[MAXN], inv_p_pow[MAXN];

// Fast modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Precompute powers and inverses
void INIT() {
    p_pow[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p_pow[i] = p_pow[i - 1] * P % M;
    }
    for (int i = 0; i < MAXN; i++) {
        inv_p_pow[i] = mod_pow(p_pow[i], M - 2, M);
    }
}


const int N = 100005;
const int LOG = 17;
vector<int> adj[N];
int up[N][LOG];
int h1[N][LOG],h2[N][LOG];
int lvl[N];
int ch[N];

void init(int n){
    for (int i = 0; i < n; ++i) {
        adj[i].clear();
        lvl[i] = 0;
        for (int j = 0; j < LOG; ++j) {
            up[i][j] = 0;
            h1[i][j] = 0;
            h2[i][j] = 0;
        }
    }
}

int merge(int a,int b){
    //
}

void dfs(int v,int p){
    for(auto to : adj[v]){
        if(to == p) continue;
        lvl[to] = lvl[v] + 1;
        up[to][0] = v;
        h1[to][0] = ch[to];
        h2[to][0] = ch[to];
        for(int j = 1 ; j < LOG; j++){
            up[to][j] = up[up[to][j-1]][j-1];
            h1[to][j] = ( h1[to][j-1] + h1[up[to][j-1]][j-1] * p_pow[(1<<(j-1))]) %M;
            h2[to][j] = ( h2[to][j-1] * p_pow[(1<<(j-1))] + h2[up[to][j-1]][j-1] ) % M ;
        }
        dfs(to,v);
    }
}   

void build(int root = 0){
    lvl[root] = 0;
    up[root][0] = root;
    h1[root][0] = h2[root][0] = 0;
    for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
            h1[root][j] = h1[root][j-1];
            h2[root][j] = h1[root][j-1];
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

int get(int u,int v){
    int lc = lca(u,v);
    int dif1 = lvl[u] - lvl[lc];
    int dif2 = lvl[v] - lvl[lc];
 
    pair<int,int> res = make_pair(0,0);
    int c1 = 0;
    for(int j = LOG-1 ; j >= 0 ; j--){
        if ((dif1 >> j) & 1) {
                res.first = (res.first +  h1[u][j] * p_pow[c1])%M;
                u = up[u][j]; c1+=(1<<j);
            }
        if ((dif2 >> j) & 1) {
                res.second = (res.second * p_pow[(1<<j)] + h2[v][j])%M;
                v = up[v][j];
        }
    }
  
    return (res.first + ch[lc] * p_pow[dif1] + res.second *  p_pow[dif1+1] )%M;
}

int find_node(int u,int v,int idx,int lc){
    int uc = lvl[u] - lvl[lc];
    int vc = lvl[v] - lvl[lc];
    if(idx <= uc) return get_kth(u,idx);
    return get_kth(v,vc-(idx-uc));
}

