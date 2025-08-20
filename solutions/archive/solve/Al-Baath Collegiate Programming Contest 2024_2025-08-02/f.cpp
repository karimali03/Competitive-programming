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
const int N = 100005;
int pre[N];
vector<pair<int,int>>g[N];
map<int,int> dp[N];
vector<pair<int,int>>queries[N];
int ans[N];

void dfs(int v,int p,int lvl){
    dp[v][lvl] = pre[v];
    for(auto [u,w] : g[v]){
        if(u == p) continue;
        pre[u] = w + pre[v];
        dfs(u,v,lvl+1);
        if(dp[u].size() > dp[v].size()) swap(dp[u],dp[v]);
    }
    for(auto [u,w] : g[v]){
        if(u == p) continue;
        for(auto [a,b] : dp[u]){
            dp[v][a] = max(dp[v][a] , b);
        }
    }
    vi x;
    for(auto [a,b] : dp[v]){
        if(x.empty()) x.push_back(b);
        else x.push_back(max(b,x.back()));
    }
    for(auto [val,idx] : queries[v]){
        auto it = lower_bound(all(x),pre[v]+val);
        if(it == x.end()) ans[idx] = -1;
        else ans[idx] = it - x.begin();
    }
}

void solve(int test_case) {
    int n; cin>>n;
    for(int i = 0 ;i  < n -1 ; i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        g[x].push_back({y,z});
        g[y].push_back({x,z});
    }
    int q; cin>>q;
    for(int i = 0 ;i < q ; i++){
        int x,y; cin>>x>>y; x--;
        queries[x].push_back({y,i});
    }
    dfs(0,-1,0);
    for(int i = 0 ; i < q ; i++) cout<<ans[i]<<"\n";
   
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