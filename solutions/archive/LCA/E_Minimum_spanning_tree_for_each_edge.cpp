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


struct LCA {
    int n, LOG;
    vector<vector<tuple<int, int, int>>> adj;
    vector<vector<int>> up;
    vector<vector<tuple<int, int>>> val;
    vector<int> depth;

    LCA(int _n) : n(_n) {
        LOG = 0;
        while ((1 << LOG) <= n) ++LOG;
        adj.resize(n);
        up = vector<vector<int>>(n, vector<int>(LOG));
        val = vector<vector<tuple<int, int>>>(n, vector<tuple<int, int>>(LOG, {-1, -1}));
        depth.assign(n, 0);
    }

    tuple<int, int> merge(const tuple<int, int>& a, const tuple<int, int>& b) {
        auto [av, ia] = a;
        auto [bv, ib] = b;
        return av > bv ? a : b;
    }

    void add_edge(int u, int v, int idx, int w = 1) {
        adj[u].emplace_back(v, w, idx);
        adj[v].emplace_back(u, w, idx);
    }

    void dfs(int v, int p) {
        for (auto [to, w, idx] : adj[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            up[to][0] = v;
            val[to][0] = {w, idx};
            for (int j = 1; j < LOG; ++j) {
                up[to][j] = up[up[to][j - 1]][j - 1];
                val[to][j] = merge(val[to][j - 1], val[up[to][j - 1]][j - 1]);
            }
            dfs(to, v);
        }
    }

    void build(int root = 0) {
        depth[root] = 0;
        up[root][0] = root;
        val[root][0] = {-1, -1};
        for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
            val[root][j] = val[root][j - 1];
        }
        dfs(root, -1);
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int j = LOG - 1; j >= 0; --j)
            if ((diff >> j) & 1)
                u = up[u][j];
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; --j)
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        return up[u][0];
    }

    tuple<int, int> get(int u, int v) {
        int c = lca(u, v);
        int dif1 = depth[u] - depth[c];
        int dif2 = depth[v] - depth[c];
        tuple<int, int> ret = {-1, -1};
        for (int j = LOG - 1; j >= 0; --j) {
            if ((dif1 >> j) & 1) {
                ret = merge(ret, val[u][j]);
                u = up[u][j];
            }
            if ((dif2 >> j) & 1) {
                ret = merge(ret, val[v][j]);
                v = up[v][j];
            }
        }
        return ret;
    }
};

struct dsu {
    vector<int> sz, par;
    int cc;
    dsu(int n) : cc(n), sz(n + 1, 1), par(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }
    bool merge(int x, int y) {
        x = get(x); y = get(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        par[x] = y;
        sz[y] += sz[x];
        cc--;
        return true;
    }
};

struct edge {
    int from, to, w, idx;
    edge(int from = -1, int to = -1, int w = -1, int idx = -1)
        : from(from), to(to), w(w), idx(idx) {}
    bool operator<(const edge& e) const {
        return w < e.w;
    }
};

pair<int, vector<bool>> mst(vector<edge> adj, int n) {
    dsu st(n);
    int cost = 0;
    sort(all(adj));
    vector<bool> vis(adj.size());
    for (auto& e : adj) {
        if (st.merge(e.from, e.to)) {
            cost += e.w;
            vis[e.idx] = true;
        }
    }
    return {cost, vis};
}

void solve(int test_case) {
    int n, m;
    cin >> n >> m;
    vector<edge> v(m);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        v[i] = {x, y, w, i};
    }
    auto [cost, vis] = mst(v, n);
    LCA lc(n);
    for (int i = 0; i < m; i++) {
        if (vis[i]) {
            lc.add_edge(v[i].from, v[i].to, v[i].idx, v[i].w);
        }
    }
    lc.build();
    for (int i = 0; i < m; i++) {
        if(vis[i]){
            cout<<cost<<ln;
        }
        else{
            auto [mx, _] = lc.get(v[i].from, v[i].to);
            cout << cost + v[i].w - mx << ln;

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
