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
vector<pair<int,int>> adj[N];
int low[N],tin[N];
bool is_bridge[N],is_arc[N];
int timer = 0;
void init(int n,int m){
    for(int i = 0 ; i < n ; i++){
        is_arc[i] = false;
        adj[i].clear();
        low[i] = 1e9; tin[i] = -1;
    }
    for(int i = 0 ; i < m ; i++) is_bridge[i] = false;
    timer = 0;
}
// replace parent with edge idx is there are multi edges between two nodes
void tarjain(int v,int p){ 
    low[v] = tin[v] = timer++;
    int kids = 0;
    for(auto [u,e] : adj[v]){ 
        if(e == p) continue;
        if(tin[u] != -1){ // back edge 
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        tarjain(u,e); // tree edge 
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) is_bridge[e] = true;
        if(p != -1 && low[u] >= tin[v]) is_arc[v] = true;
        kids++;
    }
    if(p == -1 && kids > 1) is_arc[v] = true;
}



void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n,m);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,i});
        adj[y].push_back({x,i});
    }
    f(i,0,n) if(tin[i] == -1) tarjain(i,-1);
    vi res;
    f(i,0,n) if(is_arc[i]) res.push_back(i+1);
    cout<<res.size()<<ln;
    cout<<res<<ln;
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