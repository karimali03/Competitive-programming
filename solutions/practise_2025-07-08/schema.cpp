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
int adj[N];
int vis[N];
int en[N];
bool cyc[N];
bool dfs(int u){
    if(vis[u] == 1){
        en[u] = u;
        return cyc[u] = true;
    }
    if(vis[u] == 2) return cyc[u];
    vis[u] = 1;
    vis[u] = dfs(adj[u]);
    en[u] = en[adj[u]];
    vis[u] = 2;
    return cyc[u];
}
void solve(int test_case) {
    int n; cin>>n;
    fill(vis,vis+n,0);
    fill(cyc,cyc+n,false);
    set<int>st;
    vi cnt(n);
    for(int i = 0 ; i < n ; i++){
        cin>>adj[i]; adj[i]--;
        cnt[adj[i]]++;
    }
    map<int,vi>ret;
    for(int i = 0 ; i < n ; i++){
        if(!cnt[i]) dfs(i),ret[en[i]].push_back(i);
    }
    for(int i = 0 ;i  < n ; i++) dfs(i),st.insert(en[i]);
    vector<pair<int,int>>res;
    if(st.size() > 1){
        int prv = *st.begin();
        auto it = st.begin();
        it = next(it);
        while(it != st.end()){
            if(ret.count(*it)) {
                res.push_back({prv,ret[*it].back()});
                ret[*it].pop_back();
            }
            else res.push_back({prv,*it});
            prv = *it; it = next(it); 
        }
         if(ret.count(*st.begin())) {
                res.push_back({prv,ret[*st.begin()].back()});
                ret[*st.begin()].pop_back();
            }
        else res.push_back({prv,*st.begin()});
    }
    for(auto [a,b] : ret){
        for(auto x : b) res.push_back({a,x});
    }
    cout<<res.size()<<ln;
    for(auto &it : res) cout<<it.first+1<<" "<<it.second+1<<ln;

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