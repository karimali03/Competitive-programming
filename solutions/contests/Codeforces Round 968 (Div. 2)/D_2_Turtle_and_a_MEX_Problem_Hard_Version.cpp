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

pair<int,int> mex(vi &v,int n){
    set<int>st;
    for(int i = 0 ; i <= n+1 ; i++) st.insert(i);
    for(int i = 0  ; i < n ; i++){
        if(st.count(v[i])) st.erase(v[i]);
    }
    return {*st.begin(),*(next(st.begin()))};
}


map<int,set<int>>adj;
map<int,int>ret; 
int dfs(int node){
    if(ret.count(node)) return ret[node];
    int mx = node;
    for(auto it : adj[node]){
        mx = max(mx , dfs(it));
    }
    return ret[node] = mx;
}


int sum(int l,int r){
    return r*(r+1)/2 - (l ? (l-1)*l/2 : 0);
}
void solve(int test_case) {
    adj.clear(); ret.clear();
     int n,m; cin>>n>>m;
    vec<pair<int,int>>vx(n);
    map<int,vi>init;
    for(int i = 0 ; i <  n ;i++){
        int sz; cin>>sz;
        vi v(sz); cin>>v;
        auto pr = mex(v,sz);
        adj[pr.first].insert(pr.second);
       
        vx[i] = pr;
        init[pr.first].push_back(i);
    }
    int mx = 0;
   
    for(auto [a,b] : adj){
        if(init[a].size() > 1) mx = max(mx , dfs(a));
        mx = max(mx , a);
    }
    int acc = 0;
    for(auto [a,b]  : adj ){
        if(a > m) continue;
        int r = max(mx,dfs(a));
        int op = (a > mx ? a : mx);
        if(r  > op) acc += r - op;
    }

    int res = 0;
    if(m <= mx) res = (m+1)*mx;
    else res = (mx+1)*mx + sum(mx+1,m);
    res+=acc;
    cout<<res<<ln;
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