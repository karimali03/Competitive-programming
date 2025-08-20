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
    static const int INF = 1e9;
    int n, m;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;

    HopcroftKarp(int leftSize, int rightSize) {
        n = leftSize;
        m = rightSize;
        adj.assign(n + 1, {});
        pairU.assign(n + 1, 0);
        pairV.assign(m + 1, 0);
        dist.assign(n + 1, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u == 0) return true;
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v])) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (pairU[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }

    vector<pair<int, int>> getMatchingPairs() {
        vector<pair<int, int>> result;
        for (int u = 1; u <= n; u++) {
            if (pairU[u] != 0)
                result.emplace_back(u, pairU[u]);
        }
        return result;
    }
};



void solve(int test_case) {
    int n,m; cin>>n>>m;
    vec<vec<char>>v(n,vec<char>(m));
    f(i,0,n) f(j,0,m) cin>>v[i][j];
    int sz; cin>>sz;
    string s; cin>>s;
    vii g(n,vi(m,-1));
    int a = 0,b = 0;
    for(int i = 0; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if(j+sz <= m){
                bool vld = true;
                for(int x = 0 ; x < sz ; x++) vld&=(s[x]==v[i][j+x]);
                if(vld){
                    for(int x = 0 ; x < sz ; x++) g[i][x+j] = a;
                    a++;
                }
            } 
        }
    }

    for(int j = 0 ; j < m ; j++){
        for(int i = 0 ; i < n ; i++){
            if(i+sz <= n){
                bool vld = true;
                for(int x = 0 ; x < sz ; x++) vld&=(s[x]==v[i+x][j]);
                if(vld) b++;
            }
        }
    }

    if(!a || !b){
        cout<<a+b<<ln;
        return;
    } 
    HopcroftKarp st(a,b);
    b = 0;
    for(int j = 0 ; j < m ; j++){
        for(int i = 0 ; i < n ; i++){
            if(i+sz <= n){
                bool vld = true;
                for(int x = 0 ; x < sz ; x++) vld&=(s[x]==v[i+x][j]);
                if(vld){
                    for(int x = 0 ; x < sz ; x++){
                        if(g[i+x][j] != -1) st.addEdge(g[i+x][j]+1,b+1);
                    }
                    b++;
                }
            }
        }
    }
    
 
    cout<<a+b-st.maxMatching()<<ln;
   
  
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("grid.in", "r", stdin);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}