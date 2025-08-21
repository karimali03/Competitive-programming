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
void tarjain(int v,int p){
    low[v] = tin[v] = timer++;
    int kids = 0;
    for(auto [u,e] : adj[v]){
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


pair<int, int> bfs(int start,int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int mx = 0;
    int node = start;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(auto [x,y] : adj[cur]){
            if(dist[x] == -1){
                dist[x] = dist[cur] + 1;
                if(dist[x] > mx){
                    mx = dist[x];
                    node = x;
                }
                q.push(x);
            }
        }
    }
    return {node,mx};
}

int getDiameter(int n) {
    auto [u, _] = bfs(0,n);
    auto [v, diameter] = bfs(u,n);
    return diameter;
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n,m);
    for(int i = 0 ;i <m;i++){
        int x,y; cin>>x>>y;
        adj[x-1].push_back({y-1,i});
        adj[y-1].push_back({x-1,i});
    }
    tarjain(0,-1);
    int res = getDiameter(n);
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