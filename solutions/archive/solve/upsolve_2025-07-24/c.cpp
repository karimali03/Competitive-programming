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
    edge(int _u, int _v, T _cap, T _cost, int _id)
      : u(_u), v(_v), cap(_cap), cost(_cost), id(_id) {}
  };

  int n, s, t, mxid;
  T flow, cost;
  vector<vector<int>> g;
  vector<edge> e;
  vector<T> d, potential, flow_through, edge_flow;
  vector<int> par;
  bool neg;

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
    while (flow < goal && dijkstra()) {
      flow += send_flow(t, goal - flow);
    }

    // track flow through original edges
    flow_through.assign(mxid + 10, 0);
    edge_flow.assign(e.size(), 0); // ✅ initialize class member, not local
    for (int i = 0; i < (int)e.size(); i += 2) {
      edge_flow[i] = e[i ^ 1].cap; // flow sent = reverse edge capacity
      if (e[i].id >= 0)
        flow_through[e[i].id] = e[i ^ 1].cap;
    }

    return {flow, cost};
  }

  // ✅ Safely reconstruct flow paths
  vector<vector<int>> getAllFlowPaths(int s, int t) {
    vector<vector<int>> paths;
    vector<T> used_flow = edge_flow; // copy to modify
    vector<int> ptr(n, 0);

    function<bool(int, vector<int>&)> dfs = [&](int u, vector<int>& path) {
      if (u == t) return true;
      for (int &i = ptr[u]; i < (int)g[u].size(); ++i) {
        int id = g[u][i];
        int v = e[id].v;
        if (used_flow[id] > 0) {
          used_flow[id]--;
          path.push_back(v);
          if (dfs(v, path)) return true;
          path.pop_back();
          used_flow[id]++;
        }
      }
      return false;
    };

    fill(ptr.begin(), ptr.end(), 0);
    while (true) {
      vector<int> path = {s};
      if (!dfs(s, path)) break;
      paths.push_back(path);
    }

    return paths;
  }

  // ✅ Optional: Return both path and flow along it
  vector<pair<vector<int>, T>> getAllFlowPathsWithAmounts(int s, int t) {
    vector<pair<vector<int>, T>> result;
    vector<T> used_flow = edge_flow;
    vector<int> ptr(n, 0);

    function<T(int, vector<int>&)> dfs = [&](int u, vector<int>& path) -> T {
      if (u == t) return inf;
      for (int &i = ptr[u]; i < (int)g[u].size(); ++i) {
        int id = g[u][i];
        int v = e[id].v;
        if (used_flow[id] > 0) {
          path.push_back(v);
          T f = dfs(v, path);
          if (f > 0) {
            T push = min(f, used_flow[id]);
            used_flow[id] -= push;
            return push;
          }
          path.pop_back();
        }
      }
      return 0;
    };

    fill(ptr.begin(), ptr.end(), 0);
    while (true) {
      vector<int> path = {s};
      T f = dfs(s, path);
      if (f == 0) break;
      result.emplace_back(path, f);
    }

    return result;
  }

  // --- Min Cut ---
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
};

void solve(int test_case){
    int n; cin>>n;
    int s = 2*n , t = 2*n+1;
    MCMF st(n+n+2);
    int sum = 0;
    for(int i = 0 ;i  < n ;i++){
        int x; cin>>x;
        sum+=x;
        st.add_edge(s,i,x,0);
    }    
    for(int i = 0 ; i < n ; i++){
        int x; cin>>x;
        st.add_edge(i+n,t,x,0);
    }

    for(int i = 0 ;i  < n ;i++){
        for(int j = 0 ; j  < n ; j++){
            int c; cin>>c;
            st.add_edge(i,j+n,1,-c);
        }
    }

    auto res = st.solve(s,t);
    if(res.first != sum){
        cout<<-1<<ln;
        return;
    }
    cout<<-res.second<<ln;
    vec<vec<char>>ans(n,vec<char>(n,'.'));
    auto path = st.getAllFlowPaths(s,t);
    for(auto it : path){
        ans[it[1]][it[2]-n] = 'X';
    } 

    for(int i = 0 ;i  < n ; i++){
        for(int j = 0 ; j <  n ;j++) cout<<ans[i][j];
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