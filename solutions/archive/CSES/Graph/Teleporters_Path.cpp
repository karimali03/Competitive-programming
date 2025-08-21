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


/*
 Hierholzer’s Algorithm Template
 Works for both Directed and Undirected Graphs
 A Eulerian path is a path in a graph that passes through all of its edges exactly once. A Eulerian cycle is a Eulerian path that is a cycle.
  -------------------------------
 Requirements:
     For Undirected Euler Circuit:
         - All vertices have even degree
     For Undirected Euler Path:
         - Exactly 2 vertices have odd degree
     For Directed Euler Circuit:
         - For every vertex: in-degree == out-degree
     For Directed Euler Path:
         - Exactly one vertex with out-in = 1 (start)
         - Exactly one vertex with in-out = 1 (end)
     Path lenght is m+1 is not false
     This template uses DFS + edge-marking to construct Euler path/circuit
*/

vi vis;
vec<vec<pair<int,int>>>adj;
vi path;
void dfs(int u){
    while(!adj[u].empty()){
        auto [v,id] = adj[u].back();
        adj[u].pop_back();
        if(vis[id]) continue;
        
        vis[id] = 1;
        dfs(v);
    }
    path.push_back(u);
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    vis = vi(m);
    adj = vec<vec<pair<int,int>>>(n);
    vi in(n),out(n);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,i});
        out[x]++,in[y]++;
    }
    // 1 - > n     
    int st = 0 ,en = 0;
    f(i,0,n){
        if(in[i] - out[i] == 1) en++;
        else if(out[i] - in[i] == 1) st++;
        else if(in[i] != out[i]) st = 3;
    }
    if(st != 1 || en != 1)
    cout<<"IMPOSSIBLE\n";
    else if((out[0]-in[0]) != 1 || (in[n-1]-out[n-1]) != 1)
    cout<<"IMPOSSIBLE\n";
    else{
        dfs(0);
        if(path.size() != m+1) cout<<"IMPOSSIBLE\n";
        else{
            reverse(all(path));
            for(auto it : path) cout<<it+1<<" ";
            cout<<ln;
        }
    }
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