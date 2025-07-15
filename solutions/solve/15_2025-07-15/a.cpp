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

const int N = 20;
int v[N];
int n;
int dp[1<<N];
vector<int> adj2[N];
vector<int>adj[1<<N][N];
const int LOG = 5;
int up[1<<N][N][LOG];
int lvl[1<<N][N];


void init(int n,int mask){
    for (int i = 0; i < n; ++i) {
        adj[mask][i].clear();
        lvl[mask][i] = 0;
        for (int j = 0; j < LOG; ++j) {
            up[mask][i][j] = 0;
        }
    }
}

void dfs(int v,int p,int mask){
    for(auto to : adj[mask][v]){
        if(to == p) continue;
        lvl[mask][to] = lvl[mask][v] + 1;
        up[mask][to][0] = v;
        for(int j = 1 ; j < LOG; j++){
            up[mask][to][j] = up[mask][up[mask][to][j-1]][j-1];
        }
        dfs(to,v,mask);
    }
}   

void build(int root,int mask){
    lvl[mask][root] = 0;
    up[mask][root][0] = root;
    for (int j = 1; j < LOG; ++j) {
            up[mask][root][j] = root;
    }
    dfs(root,-1 , mask);
}

int lca(int u,int v,int mask){
    if (lvl[mask][u] < lvl[mask][v]) swap(u, v);
    int diff = lvl[mask][u] - lvl[mask][v];
    for (int j = LOG - 1; j >= 0; --j)
            if ((diff >> j) & 1)  u = up[mask][u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j)
        if (up[mask][u][j] != up[mask][v][j]) {
            u = up[mask][u][j];
            v = up[mask][v][j];
        }
    return up[mask][u][0];   
}

void link(int v,int p,int last,int mask){
    if(!((mask>>v)&1ll)) last = v;
    for(auto it : adj2[v]){
        if(it == p) continue;
        if(!((mask>>it)&1)) adj[mask][last].push_back(it);
        link(it,v,last,mask);
    }
}

int rec(int mask){
    if(co(mask) >= n-1) return 0;
    int &ret = dp[mask];
    if(~ret) return ret;
    init(n,mask);
    link(0,-1,0,mask);
    build(0,mask);
    ret = 1e18;
    for(int i = 0 ; i < n ; i++){
        if( ((mask>>i)&1) || (i == 0 && co(mask) < n-2)) continue;
        for(int j = i+1 ; j < n ; j++){
            if( ((mask>>j)&1) ) continue;
            int new_mask = ((mask | (1<<i)) | (1<<j));
            int cost = v[lca(i,j,mask)];
            ret = min(ret , cost + rec(new_mask));
        }
    }
    return ret;
}
void solve(int test_case) {
    cin>>n;
    memset(dp,-1,sizeof(dp));
    f(i,0,n) cin>>v[i];
    for(int i = 0 ;i  < n-1;i++){
        int x,y; cin>>x>>y; x--,y--;
        adj2[x].push_back(y);
        adj2[y].push_back(x);
    }
    cout<<rec(0)<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}