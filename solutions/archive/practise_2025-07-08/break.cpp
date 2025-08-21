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

struct edge{
    int from,to,w;
};
const int N = 1005;
const int M = 30005;
vector<pair<int,int>>adj[N];
edge edg[M];
int vis[N]{};
int n,m;
int removed = -1;
bool findPath(int v,int p,vi &path, int en){
    vis[v] = 1;
    if(v == en) return true;
    for(auto [u,e] : adj[v]){
        if( vis[u] ) continue;
        path.push_back(e);
        if(findPath(u,v,path,en)) return true;
        else path.pop_back();
    }
    return false;
}

int low[N],tin[N];
bool is_bridge[M];
int timer = 0;
void init(int n,int m){
    for(int i = 0 ; i < n ; i++){
        low[i] = 1e9; tin[i] = -1;
    }
    for(int i = 0 ; i < m ; i++) is_bridge[i] = false;
    timer = 0;
}
bool tarjain(int v,int p , vi &path , int en ,bool stop){
    low[v] = tin[v] = timer++;
    if(en == v) stop = true;
    for(auto [u,e] : adj[v]){
        if(e == p || e == removed ) continue;
        if(tin[u] != -1){ // back edge
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        if(!stop) path.push_back(e);
        if(!tarjain(u,e,path,en,stop)) path.pop_back();
        else stop = true; 
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) is_bridge[e] = true;
    }
    return stop;
}

void solve(int test_case) {
    cin>>n>>m;
    int s,t; cin>>s>>t; s--,t--;
    for(int i = 0 ; i < m ; i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        adj[x].push_back({y,i});
        adj[y].push_back({x,i});
        edg[i] = {x,y,z};
    }
    vi path;
    if(!findPath(s,-1,path,t)) return void(cout<<"0\n0\n");
    int res = 1e10;
    pair<int,int> ret = {-1,-1};
    for(auto it : path){
        removed = it;
        init(n,m);
        vi row; 
        tarjain(s,-1,row,t,false);
        int ans = edg[it].w;
        if(row.empty() && ans < res){
            res = ans;
            ret.first = removed; ret.second = -1;
        }
        for(auto x : row) if(is_bridge[x] && ans+edg[x].w < res){
            res = ans+edg[x].w;
            ret.first = removed , ret.second = x;
        }
    }
    if(res == 1e10) cout<<-1<<ln;
    else{
        cout<<res<<ln;
        int cnt = (ret.first != -1) + (ret.second != -1);
        cout<<cnt<<ln;
        if(ret.first != -1) cout<<ret.first+1;
        if(ret.second != -1) cout<<" "<<ret.second+1;
        cout<<ln;
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