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
Any set of more than k numbers in which all numbers are in the range 
that can be represented using at most k bits, 
must contain a subset with XOR = 0.
k+1 number -> xor zero
*/
// 20 bit -> 21 number 


const int N = 300005;
vector<int> adj[N],adj2[N];
int tin[N], low[N], timer;
int comp[N], comp_cnt;
vector<int> comps[N];
int sz[N];
stack<int> st;
bool on_stack[N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        adj2[i].clear(); 
        sz[i] = 0;
        tin[i] = low[i] = -1;
        comp[i] = -1;
        comps[i].clear();
        on_stack[i] = false;
    }
    while (!st.empty()) st.pop();
    timer = comp_cnt = 0;
}

void dfs(int v) {
    tin[v] = low[v] = timer++;
    st.push(v);
    on_stack[v] = true;

    for (int u : adj[v]) {
        if (tin[u] == -1) {
            dfs(u);
            low[v] = min(low[v], low[u]);
        } else if (on_stack[u]) {
            low[v] = min(low[v], tin[u]);
        }
    }

    if (low[v] == tin[v]) {
        while (true) {
            int u = st.top(); st.pop();
            comp[u] = comp_cnt;
            on_stack[u] = false;
            if (u == v) break;
        }
        comp_cnt++;
    }
}



struct XorBasis {
    static const int LOG = 21;
    long long basis[LOG];
    int inserted = 0;

    XorBasis() {
        memset(basis, 0, sizeof(basis));
    }

    void insert(long long x) {
        inserted++;
        for (int i = LOG - 1; i >= 0; --i) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }

    int size() const {
        int cnt = 0;
        for (int i = 0; i < LOG; ++i)
            if (basis[i]) cnt++;
        return cnt;
    }
    // non empty 
    bool XrZero() const {
        return size() < inserted;
    }
};


bool explore(int v,int cnt,XorBasis st,int n){
    cnt+=sz[v];
    for(auto &it : comps[v]) st.insert(it);
    if(v == comp[n-1]) return st.XrZero();
    if(cnt > 20) return false;
    for(auto x : adj2[v]){
        if(explore(x,cnt,st,n)) return true;
    }
    return false;
}

int vis[N];
void topo(int v,vi &path){
    vis[v] = 1;
    for(auto it : adj2[v]) if(!vis[it]) topo(it,path);
    path.push_back(v);
}

void solve(int test_case) {
    int n; cin>>n;
    init(n);
    vii v(n,vi(2));
    for(int i = 0 ;i  < n ;i++){
        cin>>v[i];
        for(int x = 0 ;x  < 2 ; x++) if(v[i][x]) adj[i].push_back(v[i][x]-1);
    }
    vi a(n); cin>>a;
    f(i,0,n) if(tin[i] == -1) dfs(i);
    f(i,0,n){
        sz[comp[i]]++;
        comps[comp[i]].push_back(a[i]);
    }
    vi cnt(comp_cnt);
    for(int i = 0 ; i < n ; i++){
        for(int x = 0 ;x < 2 ; x++){
            if(v[i][x] && comp[v[i][x]-1] != comp[i]){
                adj2[comp[i]].push_back(comp[v[i][x]-1]);
                cnt[comp[v[i][x]-1]]++;
            } 
        }
    }
    vi path;
    fill(vis,vis+comp_cnt,0);
    f(i,0,comp_cnt) if(cnt[i] == 0) topo(i,path);
    
    vi dp(comp_cnt,-1e9);
    for(auto x : path){
        if(x == comp[n-1]) dp[x] = sz[x];
        for(auto it : adj2[x]){
            if(dp[it] == -1e9) continue;
            dp[x] = max(dp[x] , sz[x] + dp[it]);
        }
    }
    if(dp[comp[0]] >= 21){
        YES;
        return;
    }
    XorBasis st;
    if(explore(comp[0],0,st,n)) YES;
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