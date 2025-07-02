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

const int N = 1e5 + 5;
vector<int> adj[N]; // input graph
int tin[N], low[N], timer;
bool visited[N];
bool is_cut[N];
vector<pair<int, int>> bridges;
int comp[N];        // component ID
vector<int> tree[N]; // bridge tree

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;

    for (int to : adj[v]) {
        if (to == p) continue;

        if (visited[to]) {
            // back edge
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);

            // bridge
            if (low[to] > tin[v])
                bridges.push_back({v, to});

            // articulation point
            if (low[to] >= tin[v] && p != -1)
                is_cut[v] = true;

            children++;
        }
    }

    if (p == -1 && children > 1)
        is_cut[v] = true;
}

void dfs_comp(int v, int cid) {
    comp[v] = cid;
    for (int to : adj[v]) {
        if (comp[to] != -1) continue;
        // skip bridges
        if (find(bridges.begin(), bridges.end(), make_pair(v, to)) != bridges.end() ||
            find(bridges.begin(), bridges.end(), make_pair(to, v)) != bridges.end()) continue;
        dfs_comp(to, cid);
    }
}

int build_bridge_tree(int n) {
    memset(comp, -1, sizeof(comp));
    int cid = 0;
    for (int i = 0; i < n; ++i) {
        if (comp[i] == -1)
            dfs_comp(i, cid++);
    }

    for (auto [u, v] : bridges) {
        int cu = comp[u], cv = comp[v];
        if (cu != cv) {
            tree[cu].push_back(cv);
            tree[cv].push_back(cu);
        }
    }
    return cid;
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    for(int i = 0 ;i  < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
    }
    dfs(0);
    cout<<build_bridge_tree(n)-1<<ln;
    for(auto it : bridges){
        cout<<it.first+1<<" "<<it.second+1<<ln;
    }
    for(int i = 0; i  <n ; i++){
        cout<<comp[i]<<" ";
    }
    cout<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}