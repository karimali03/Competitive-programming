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


struct HopcroftKarp {
  static const int inf = 1e9;
  int n;
  vector<int> l, r, d;
  vector<vector<int>> g;
  HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v + n); //right id is increased by n, so is l[u]
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) d[u] = 0, q.push(u);
      else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[r[v]] == inf) {
          d[r[v]] = d[u] + 1;
          q.push(r[v]);
        }
      }
    }
    return d[0] != inf;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (auto v : g[u]) {
      if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
        l[u] = v;
        r[v] = u;
        return true;
      }
    }
    d[u] = inf;
    return false;
  }
  int maximum_matching() {
    int ans = 0;
    while (bfs()) {
      for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
    }
    return ans;
  }
};

const int N = 1005;
char v[N][N];
int g[N][N],gg[N][N];
void solve(int test_case) {
    int n,m; cin>>n>>m;
    f(i,0,n) f(j,0,m) cin>>v[i][j];
    int sz; cin>>sz;
    string s; cin>>s;

    if (sz == 1) {
      ll sol = 0;
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          sol += (v[i][j] == s[0]);
        }
        
      }
      cout << sol << '\n';
      return;
    }
    f(i,0,n) f(j,0,m) g[i][j] = gg[i][j] = 0;
    int a = 0,b = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j <= m-sz ; ){
            if(s[0] != v[i][j]){
              j++; continue;
            }
            int st = j;
            while(j-st < sz && s[j-st] == v[i][j]) j++;
            if( j-st != sz) continue;
            g[i][st]+=(a+1);
            if(j < m) g[i][j]-=(a+1);
            a++;
        }
    }



    for(int j = 0 ; j < m ; j++){
        for(int i = 0 ; i <= n-sz ; ){
            if(s[0] != v[i][j]){
              i++; continue;
            }
            int st = i;
            while( i-st < sz && s[i-st] == v[i][j]) i++;
            if( i-st != sz) continue;
            gg[st][j]+=(b+1);
            if(i < n) gg[i][j]-=(b+1);
            b++;
        }
    }

    if(!a || !b){
        cout<<a+b<<ln;
        return;
    }

    HopcroftKarp st(a,b);
    for(int i = 0 ; i < n ; i++){
      for(int j = 1 ; j < m ; j++) g[i][j]+=g[i][j-1];
    }
    for(int j = 0 ; j < m ; j++){
       for(int i = 1 ; i < n ; i++) gg[i][j]+=gg[i-1][j];
    }
    for(int i = 0 ; i < n ; i++){
      for(int j = 0 ; j < m ; j++){
          if(g[i][j] && gg[i][j]) st.add_edge(g[i][j],gg[i][j]);
      }
    }
    cout<<a+b-st.maximum_matching()<<ln;
  
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen("grid.in", "r", stdin);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}