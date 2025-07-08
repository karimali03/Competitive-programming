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

const int N = 300005;
vector<tuple<int,int,int>> adj[N];
int low[N],tin[N];
bool is_bridge[N],is_arc[N];
int timer = 0;
int id[N];
vector<pair<int,int>> adj2[N];
int val[N]{};
void init(int n,int m){
    for(int i = 0 ; i < n ; i++){
        is_arc[i] = false;
        adj[i].clear();
        adj2[i].clear();
        low[i] = 1e9; tin[i] = id[i] =  -1;
    }
    for(int i = 0 ; i < m ; i++) is_bridge[i] = false;
    timer = 0;
}
void tarjain(int v,int p){
    low[v] = tin[v] = timer++;
    int kids = 0;
    for(auto [u,e,z] : adj[v]){
        if(u == p) continue;
        if(tin[u] != -1){ // back edge
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        tarjain(u,v); // tree edge
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) is_bridge[e] = true;
        if(p != -1 && low[u] >= tin[v]) is_arc[v] = true;
        kids++;
    }
    if(p == -1 && kids > 1) is_arc[v] = true;
}

void bridge_tree(int v,int p , int x){
    id[v] = x;
    for(auto [u,e,z] : adj[v]){
        if(u == p) continue;
        if(is_bridge[e]) bridge_tree(u,v,u);
        else if(id[u] == -1) bridge_tree(u,v,x);
    }
}


int dfs(int u,int p,int res , int to){
    res += val[u];
    if(u == to) return res>0;
    bool ret = false;
    for(auto [a,b] : adj2[u]){
        if(a == p) continue;
        ret|=dfs(a,u,res+b,to);
    }
    return ret;
}
void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n,m);
    vector<pair<int,pair<int,int>>>edg(m);
    for(int i=0;i<m;i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        adj[x].push_back({y,i,z});
        adj[y].push_back({x,i,z});
        edg[i] = {z,{x,y}};
    }
    int a,b; cin>>a>>b; a--,b--;
    tarjain(0,-1);
    bridge_tree(0,-1,0);
    for(int i = 0 ; i < m ; i++){
        int x = edg[i].second.first , y = edg[i].second.second;
        int z = edg[i].first;
        if(id[x] == id[y]) val[id[x]]+=z;
        else{
            adj2[id[x]].push_back({id[y],z});
            adj2[id[y]].push_back({id[x],z});
        }
    }
    if(dfs(id[a],-1,0,id[b])) YES;
    else NO;

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