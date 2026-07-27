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

void solve() {
    int n, m; 
    cin >> n >> m;
    
    // array<int, 4> usage: [0] = u, [1] = v, [2] = color, [3] = id
    vector<array<int, 4>> edges(m);
    vii g(n); // Zero-based indexing, size is exactly n
    vi color(n, 0);
    vi dist_to_n(n, -1);
    bool vld = true;
    
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        
        // Convert to zero-based indexing
        edges[i][0]--;
        edges[i][1]--;
        edges[i][3] = i;
        
        if (edges[i][2] == 1) {
            g[edges[i][0]].push_back(edges[i][1]);
        }
    }
    
    int target = n - 1; // n is the destination, which is n-1 in zero-based
    
    function<void(int)> dfs = [&](int u) {
        color[u] = 1; 
        dist_to_n[u] = (u == target) ? 0 : -1; 
        
        for (auto &v : g[u]) {
            if (color[v] == 1) { // Cycle detected
                vld = false;
                return;
            }
            if (color[v] == 0) { 
                dfs(v);
                if (!vld) return;
            }
            
            // Dead end check
            if (dist_to_n[v] == -1) {
                vld = false;
                return;
            }
            
            // Longest path computation
            dist_to_n[u] = max(dist_to_n[u], dist_to_n[v] + 1);
        }
        color[u] = 2; 
    };
    
    // Start DFS strictly from node 0 (which was node 1)
    dfs(0);
    
    if (!vld || dist_to_n[0] == -1) {
        NA; 
        return;
    }
    
    // Check for stranded black edges
    for (int i = 0; i < m; ++i) {
        if (edges[i][2] == 1 && color[edges[i][0]] == 0) {
            NA; 
            return;
        }
    }

    // Assign and print weights
    for (int i = 0; i < m; ++i) {
        if (edges[i][2] == 1) {
            cout << dist_to_n[edges[i][0]] - dist_to_n[edges[i][1]] << (i == m - 1 ? "" : " ");
        } else {
            cout << 1000000000 << (i == m - 1 ? "" : " ");
        }
    }
    cout << ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve();
    }

    return 0;
}