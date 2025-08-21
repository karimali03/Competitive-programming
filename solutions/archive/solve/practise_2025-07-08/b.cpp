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

vector<pair<int,int>>res;

bool tarjain(int v,int p){
    low[v] = tin[v] = timer++;
    bool ret = true;
    for(auto [u,e] : adj[v]){
        if(u == p) continue;
        if(!is_bridge[e]) res.push_back({v,u});
        is_bridge[e] = true;
        if(tin[u] != -1){ // back edge
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        ret&=tarjain(u,v); // tree edge
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) return false;
    }
   
    return ret;
}
void solve(int test_case) {
    int n,m; cin>>n>>m;
    init(n,m);
    vector<pair<int,int>>edg(m);
    for(int i=0;i<m;i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,i});
        adj[y].push_back({x,i});
        edg[i] = {x,y};
    }
    if(!tarjain(0,-1)) cout<<"0";
    else{
        for(auto [a,b] : res){
            cout<<a+1<<" "<<b+1<<ln;
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