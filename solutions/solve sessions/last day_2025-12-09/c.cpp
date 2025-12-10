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

const int N = 3e5 + 9;

/*given a simple undirected graph with n nodes and m edges
with no self loops or multiple edges
find the number of 3 and 4 length cycles
two cycles are different if their edge collections are different*/
vector<int> g[N], G[N];
int val[N];
int deg[N];//degrees, precalc it
//m.sqrt(m)
long long cycle3(int n) {
  int i, x;
  long long w = 0;
  for(i = 1; i <= n; i++) G[i].clear();
  for(i = 1; i <= n; i++) val[i] = 0;
  for(i = 1; i <= n; i++) {
    for(auto e : g[i]) {
      if(e < i) continue;
      if(deg[i] <= deg[e]) G[i].push_back(e);
      else G[e].push_back(i);
    }
  }
  for(i = 1; i <= n; i++) {
    for(auto u : G[i]) val[u] = i;
    for(auto e : g[i]) {
      if(e < i) continue;
      //x = deg[i] + deg[e] - 3;
      for(auto v : G[e]) {
        if(val[v] == i) {
          w++;
          //w+=x + deg[v] - 2;//for number of 3-cycles with or without an extra edge
          //connected to any node of the cycle
        }
      }
    }
  }
  return w;
}
//m.sqrt(m)
long long cycle4(int n) {
  int i,x;
  long long w = 0;
  for(i = 1; i <= n; i++) G[i].clear();
  for(i = 1; i <= n; i++) val[i] = 0;
  for(i = 1; i <= n; i++) {
    for(auto e : g[i]) {
      if(e < i) continue;
      if(deg[i] <= deg[e]) G[i].push_back(e);
      else G[e].push_back(i);
    }
  }
  for(i = 1; i <= n; i++) {
    for(auto u : g[i]) {
      for(auto v : G[u]) {
        if(deg[v] > deg[i] || (deg[v] == deg[i] && v > i)) w += val[v]++;
      }
    }
    for(auto u : g[i]) {
      for(auto v : G[u]) val[v] = 0;
    }
  }
  return w;
}


void solve(int test_case) {
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }
  for(int i = 1; i <= n; i++) deg[i] = g[i].size();
  cout << cycle3(n);
  // << ' ' << cycle4(n) << '\n';
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