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
vector<pair<int,int>> adj[N];
int low[N],tin[N];
bool is_bridge[N];
int timer = 0;
void init(int n,int m){
    for(int i = 0 ; i < n ; i++){
        adj[i].clear();
        low[i] = 1e9; tin[i] = -1;
    }
    for(int i = 0 ; i < m ; i++) is_bridge[i] = false;
    timer = 0;
}
void tarjain(int v,int p){ // replace p with e is there are multi edges between two nodes
    low[v] = tin[v] = timer++;
    for(auto [u,e] : adj[v]){ 
        if(u == p) continue;
        if(tin[u] != -1){ // back edge 
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        tarjain(u,v); // tree edge 
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) is_bridge[e] = true;
    }
  
}
void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n,m);
    vii v(m);
    vi seen(n);
    for(int i = 0 ;i  < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,i});
        adj[y].push_back({x,i});
        v[i].push_back(x); v[i].push_back(y);
    }
    tarjain(0,-1);
    set<int> brid;
    vi seen2(n);
    function<bool(int)> dfs = [&](int i) -> bool {
        if(seen2[i] != 0) return seen2[i] == 1;
        if(i == n-1) return seen2[i] = 1;
        seen2[i] = -1; 
        for(auto [a, _] : adj[i]){
            if(seen2[a] == -1) continue; 
            if(dfs(a)){
                if(is_bridge[_]) brid.insert(_);
                seen2[i] = 1;
            } 
        }
        return seen2[i];
    };
    dfs(0);
    for(int i = 0 ;i  < m; i++) is_bridge[i] = false;
    priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,greater<>>q;
    for(auto it : brid){
        is_bridge[it] = true;
        for(auto x : v[it]){
            q.push({{0,it},x}); 
        }
    }
    vi res(n,-1);
    while (!q.empty()){
        auto [b,a] = q.top(); q.pop();
        if(res[a] != -1) continue;
     //   cout<<a+1<<" "<<b+1<<ln;
        res[a] = b.second;
        for(auto [x,y] : adj[a]){
            if(res[x] != -1) continue;
            q.push({{b.first+1,b.second},x});
        }
    }
    int sz; cin>>sz;
    vi qu(sz); cin>>qu;
    bool vld = false;
    for(int i = 0; i < m ; i++) vld|=is_bridge[i];
    if(!vld){
        NA; return;
    }
    for(auto it : qu){
        cout<<res[it-1]+1<<" ";
    }
    cout<<ln;
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}