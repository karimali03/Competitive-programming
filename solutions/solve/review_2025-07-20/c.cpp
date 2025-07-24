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


const int MAXV = 1005;
const int INF = 1e17;

struct PushRelabel {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

    vector<Edge> adj[MAXV];
    int excess[MAXV], height[MAXV];
    int n, s, t;

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i < n; ++i)
            adj[i].clear();
    }

    void addEdge(int u, int v, int cap, bool directed = true) {
        adj[u].push_back({v, (int)adj[v].size(), cap, 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, directed ? 0 : cap, 0});
    }

    void push(int u, Edge &e) {
        int v = e.to;
        int d = min(excess[u], e.cap - e.flow);
        if (height[u] == height[v] + 1 && d > 0) {
            e.flow += d;
            adj[v][e.rev].flow -= d;
            excess[u] -= d;
            excess[v] += d;
        }
    }

    void relabel(int u) {
        int d = INF;
        for (Edge &e : adj[u])
            if (e.cap > e.flow)
                d = min(d, height[e.to]);
        if (d < INF)
            height[u] = d + 1;
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            bool pushed = false;
            for (Edge &e : adj[u]) {
                if (e.cap > e.flow && height[u] == height[e.to] + 1) {
                    push(u, e);
                    pushed = true;
                    if (excess[u] == 0) break;
                }
            }
            if (!pushed) relabel(u);
        }
    }

    int maxFlow() {
        fill(excess, excess + n, 0);
        fill(height, height + n, 0);
        height[s] = n;

        for (Edge &e : adj[s]) {
            e.flow = e.cap;
            adj[e.to][e.rev].flow = -e.cap;
            excess[e.to] += e.cap;
            excess[s] -= e.cap;
        }

        vector<int> list;
        for (int i = 0; i < n; ++i)
            if (i != s && i != t) list.push_back(i);

        int p = 0;
        while (p < (int)list.size()) {
            int u = list[p];
            int oldHeight = height[u];
            discharge(u);
            if (height[u] > oldHeight) {
                rotate(list.begin(), list.begin() + p, list.begin() + p + 1);
                p = 0;
            } else {
                ++p;
            }
        }

        return accumulate(adj[s].begin(), adj[s].end(), 0LL, [](int sum, Edge &e) {
            return sum + e.flow;
        });
    }

    vector<vector<int>> paths;

    bool dfs_path(int u, vector<int>& path, vector<bool>& vis) {
        if (u == t) {
            paths.push_back(path);
            return true;
        }
        vis[u] = true;
        for (auto &e : adj[u]) {
            if (e.flow > 0 && !vis[e.to]) {
                path.push_back(e.to);
                e.flow--; // mark flow unit used
                if (dfs_path(e.to, path, vis)) return true;
                path.pop_back();
                e.flow++; // backtrack
            }
        }
        return false;
    }

    vector<vector<int>> getAllFlowPaths() {
        paths.clear();
        while (true) {
            vector<int> path = {s};
            vector<bool> vis(n, false);
            if (!dfs_path(s, path, vis)) break;
        }
        return paths;
    }


    vector<bool> vis;

    void dfs_min_cut(int u) {
        vis[u] = true;
        for (auto &e : adj[u]) {
            if (!vis[e.to] && e.cap > e.flow) { // Residual capacity exists
                dfs_min_cut(e.to);
            }
        }
    }

    vector<pair<int, int>> getMinCut() {
        vis.assign(n, false);
        dfs_min_cut(s);

        vector<pair<int, int>> cut;
        for (int u = 0; u < n; ++u) {
            if (!vis[u]) continue;
            for (auto &e : adj[u]) {
                if (!vis[e.to] && e.cap > 0) {
                    cut.emplace_back(u, e.to); // Edge from reachable to unreachable
                }
            }
        }
        return cut;
    }


    
};



void solve(int test_case) {
    int n,m; cin>>n>>m;
    PushRelabel st;
    st.init(n,0,n-1);
    for(int i = 0 ;i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        st.addEdge(x,y,1);
    }
    cout<<st.maxFlow()<<ln;
    auto res = st.getAllFlowPaths();
    for(auto &it : res){
        cout<<it.size()<<ln;
        for(auto x : it) cout<<x+1<<" ";
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