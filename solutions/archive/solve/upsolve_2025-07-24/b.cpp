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


using T = long long;
const T inf = 1LL << 61;
struct MCMF {
  struct edge {
    int u, v;
    T cap, cost;
    int id;
    edge(int _u, int _v, T _cap, T _cost, int _id) : u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
  };

  int n, s, t, mxid;
  T flow, cost;
  vector<vector<int>> g;
  vector<edge> e;
  vector<T> d, potential, flow_through;
  vector<int> par;
  bool neg;

  vector<bool> used_in_path;

  MCMF() {}
  MCMF(int _n) {
    n = _n + 10;
    g.assign(n, vector<int>());
    neg = false;
    mxid = 0;
  }

  void add_edge(int u, int v, T cap, T cost, int id = -1, bool directed = true) {
    if (cost < 0) neg = true;
    g[u].push_back(e.size());
    e.push_back(edge(u, v, cap, cost, id));
    g[v].push_back(e.size());
    e.push_back(edge(v, u, 0, -cost, -1));
    mxid = max(mxid, id);
    if (!directed) add_edge(v, u, cap, cost, -1, true);
  }

  bool dijkstra() {
    par.assign(n, -1);
    d.assign(n, inf);
    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<>> q;
    d[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
      int u = q.top().second;
      T nw = q.top().first;
      q.pop();
      if (nw != d[u]) continue;
      for (int id : g[u]) {
        int v = e[id].v;
        T cap = e[id].cap;
        T w = e[id].cost + potential[u] - potential[v];
        if (d[u] + w < d[v] && cap > 0) {
          d[v] = d[u] + w;
          par[v] = id;
          q.push({d[v], v});
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (d[i] < inf) d[i] += (potential[i] - potential[s]);
    }
    for (int i = 0; i < n; i++) {
      if (d[i] < inf) potential[i] = d[i];
    }
    return d[t] != inf;
  }

  T send_flow(int v, T cur) {
    if (par[v] == -1) return cur;
    int id = par[v];
    int u = e[id].u;
    T w = e[id].cost;
    T f = send_flow(u, min(cur, e[id].cap));
    cost += f * w;
    e[id].cap -= f;
    e[id ^ 1].cap += f;
    return f;
  }

  pair<T, T> solve(int _s, int _t, T goal = inf) {
    s = _s;
    t = _t;
    flow = 0, cost = 0;
    potential.assign(n, 0);
    if (neg) {
      d.assign(n, inf);
      d[s] = 0;
      bool relax = true;
      for (int i = 0; i < n && relax; i++) {
        relax = false;
        for (int u = 0; u < n; u++) {
          for (int id : g[u]) {
            int v = e[id].v;
            T cap = e[id].cap, w = e[id].cost;
            if (d[v] > d[u] + w && cap > 0) {
              d[v] = d[u] + w;
              relax = true;
            }
          }
        }
      }
      for (int i = 0; i < n; i++) if (d[i] < inf) potential[i] = d[i];
    }
    while (flow < goal && dijkstra()) flow += send_flow(t, goal - flow);
    flow_through.assign(mxid + 10, 0);
    for (int u = 0; u < n; u++) {
      for (int id : g[u]) {
        if (e[id].id >= 0) flow_through[e[id].id] = e[id ^ 1].cap;
      }
    }
    return {flow, cost};
  }

  bool dfs_path(int u, int t, vector<int> &path) {
    if (u == t) return true;
    for (int id : g[u]) {
      edge &e1 = e[id];
      if (e1.cap == 0 && !used_in_path[id]) {
        used_in_path[id] = true;
        path.push_back(e1.v);
        if (dfs_path(e1.v, t, path)) return true;
        path.pop_back();
        used_in_path[id] = false;
      }
    }
    return false;
  }

  vector<vector<int>> getAllFlowPaths(int s, int t) {
    used_in_path.assign(e.size(), false);
    vector<vector<int>> flow_paths;
    while (true) {
      vector<int> path = {s};
      if (!dfs_path(s, t, path)) break;
      flow_paths.push_back(path);
    }
    return flow_paths;
  }

  vector<bool> vis;

  void dfs_residual(int u) {
    vis[u] = true;
    for (int id : g[u]) {
      int v = e[id].v;
      if (!vis[v] && e[id].cap > 0) {
        dfs_residual(v);
      }
    }
  }

  // Returns list of edges (u, v) in the min cut
  vector<pair<int, int>> getMinCut(int s) {
    vis.assign(n, false);
    dfs_residual(s);
    vector<pair<int, int>> cut;
    for (int u = 0; u < n; ++u) {
      if (!vis[u]) continue;
      for (int id : g[u]) {
        auto &ed = e[id];
        if (ed.cap == 0 && !vis[ed.v]) {
          cut.emplace_back(u, ed.v);
        }
      }
    }
    return cut;
  }


};


void solve(int test_case) {
    int n; cin>>n;
    MCMF st(2*n+2);
    for(int i = 0 ; i <  n ;i++) st.add_edge(2*n,i,1,0);
    for(int i = n ; i < 2*n ; i++) st.add_edge(i,2*n+1,1,0);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            int c; cin>>c;
            st.add_edge(i,j+n,1,c);
        }
    }
    auto res = st.solve(2*n,2*n+1);
    cout<<res.second<<ln;
    auto ret = st.getAllFlowPaths(2*n,2*n+1);
    for(auto &it : ret) cout<<it[1]+1<<" "<<it[2]-n+1<<ln;
    
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