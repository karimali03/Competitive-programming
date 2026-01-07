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

const int OO = 1e18;

struct edge {
        int from, to, w;
        edge(int from=0, int to=0, int w=0) :
        from(from), to(to), w(w) {
        }
};

vi BellmanFord(vector<edge> &edgeList, int n, int src) {
    vector<int> dist(n, OO);
    dist[src] = 0;

    // PHASE 1: Find shortest paths (N-1 iterations)
    // Relax edges only if the 'from' node is reachable
    for (int it = 0; it < n - 1; ++it) {
        for (const auto &ne : edgeList) {
            if (dist[ne.from] < OO) { // <--- CRITICAL CHECK ADDED
                if (dist[ne.to] > dist[ne.from] + ne.w) {
                    dist[ne.to] = max(-OO, dist[ne.from] + ne.w);
                }
            }
        }
    }

    // PHASE 2: Propagate Negative Infinity (N iterations)
    // If a node can still be relaxed, or its parent is -OO, set it to -OO
    for (int it = 0; it < n; ++it) {
        for (const auto &ne : edgeList) {
            if (dist[ne.from] < OO) { // Only propagate from reachable nodes
                if (dist[ne.to] > dist[ne.from] + ne.w || dist[ne.from] == -OO) {
                    dist[ne.to] = -OO;
                }
            }
        }
    }

    return dist;
}
void solve(int test_case) {
    int n,m,s; cin>>n>>m>>s; s--;
    vector<edge>g(m);
    for(int i =0;i < m ; i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        g[i] =  {x,y,w};
    }
    auto d = BellmanFord(g,n,s);
    for(int i = 0 ; i < n ;i++){
        if(d[i] == -OO) cout<<"-\n";
        else if(d[i] == OO) cout<<"*\n";
        else cout<<d[i]<<"\n";
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