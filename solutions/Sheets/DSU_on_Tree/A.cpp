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

const int MAXN = 200005;
vector<int> g[MAXN];
int sz[MAXN], bigChild[MAXN];
int color[MAXN];
// Global data structure (e.g., frequency array, max variables)
int freq[MAXN]; 

// preprocess the tree to compute sizes and identify big children
void getSize(int u, int p) {
    sz[u] = 1;
    bigChild[u] = 0;
    int maxSubtree = 0;
    
    for (int v : g[u]) {
        if (v != p) {
            getSize(v, u);
            sz[u] += sz[v];
            if (sz[v] > maxSubtree) {
                maxSubtree = sz[v];
                bigChild[u] = v;
            }
        }
    }
}

// add or remove the contribution of a subtree rooted at 'u' to the global data structure
void add(int u, int p, int delta) {
    freq[color[u]] += delta;
    
    for (int v : g[u]) {
        if (v != p) {
            add(v, u, delta);
        }
    }
}

// Main Sack DFS function
void dfs(int u, int p, bool keep) {
    // 1. Process all "light" children and remove their data afterwards
    for (int v : g[u]) {
        if (v != p && v != bigChild[u]) {
            dfs(v, u, false); // false = do not keep in global structure
        }
    }
    
    // 2. Process the "big" child and keep its data
    if (bigChild[u] != 0) {
        dfs(bigChild[u], u, true); // true = keep
    }
    
    // 3. Add the contributions of the current node and all light children back
    freq[color[u]] += 1; // add current node
    for (int v : g[u]) {
        if (v != p && v != bigChild[u]) {
            add(v, u, 1); // add light subtrees
        }
    }
    
    // 4. Answer queries for subtree 'u' here
    // ans[u] = ...
    
    // 5. If we shouldn't keep the data (because 'u' is a light child itself), clean up
    if (!keep) {
        add(u, p, -1);
    }
}

void solve(int test_case) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}