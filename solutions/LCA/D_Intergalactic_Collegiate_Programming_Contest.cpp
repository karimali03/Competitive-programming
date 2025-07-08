#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}








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
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        dp1[i] = dp2[i] = cnt[i] = 0;
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

void rec(int u,int p,int n){
    cnt[u] = 1;
    dp1[u] = 0;
    for(auto [it,w] : adj[u]){
        if(it == p) continue;
        rec(it,u,n);
        dp1[u] += w * cnt[it] + dp1[it];
        cnt[u]+=cnt[it];
    }
}

void rec2(int u, int p,int n) {
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dp2[v] = dp2[u] + dp1[u] - (dp1[v] + cnt[v] * w) + (n - cnt[v]) * w;
        rec2(v, u , n);
    }
}


void solve(int test_case) {
    int n,q; cin>>n>>q;
    init(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y,w; cin >> x >> y >> w;
        x--, y--;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    build();
    rec(0, -1 , n);     
    rec2(0, -1 , n); 
    while(q--){
        int s,r; cin>>s>>r; s--,r--;
        int lc = lca(s,r);
        int ret =0 ;
        if(lc == r)
        ret = dp1[s] + dp2[s] - dp2[r] - get_dist(s,r) * (n - cnt[r]);
        else  ret = dp1[r] + cnt[r] * get_dist(s,r);
        cout<<ret<<ln;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("subtree.in", "r", stdin);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}