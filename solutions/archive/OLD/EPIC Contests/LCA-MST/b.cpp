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

struct LCA{
    int LOG,n;
    vii g,up;
    vi lvl;
    LCA(vii &g) :g(g){
        n = g.size();
        LOG = __lg(n) + 1;
        up = vii(n,vi(LOG));
        lvl = vi(n);
    };

    void build(){
        up[0][0] = 0;
        lvl[0] = 0;
        for(int i = 1 ; i < LOG; i++) up[0][i] = 0;
        dfs(0,0);
    }

    void dfs(int u,int p){
        for(auto v : g[u]) if(v != p){
            up[v][0] = u;
            lvl[v] = 1 + lvl[u];
            for(int lg = 1 ; lg < LOG ; lg++){
                up[v][lg] = up[up[v][lg-1]][lg-1];
            }
            dfs(v,u);
        }
    }

    int get_kth(int u,int k){
        for(int i = 0;i < LOG ; i++){
            if((k>>i)&1) u = up[u][i];
        }
        return u;
    }

    int lca(int u,int v){
        if(lvl[u] > lvl[v]) swap(u,v);
        v = get_kth(v,lvl[v]-lvl[u]);
        if(u == v) return u;
        for(int i = LOG-1 ; i >= 0 ; i--){
            if(up[v][i] != up[u][i]){
                v = up[v][i];
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    int get_dist(int u,int v){
        int lc = lca(u,v);
        return lvl[u] + lvl[v] - 2 * lvl[lc];
    }
};

void solve(int test_case) {
    int n, m;
    cin>>n>>m;

    // Building the graph
    // The input gives the parent for nodes 1 to n-1. 
    // Node 0 is the root.
    vii g(n);
    for(int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    LCA tree(g);
    tree.build();

    int a1, a2;
    cin >> a1 >> a2;

    int x, y, z;
    cin >> x >> y >> z;

    int v_last = 0;
    int total_sum = 0;

    // These variables hold a_{i-2} and a_{i-1}
    int seq_prev2 = a1; 
    int seq_prev1 = a2; 

    for(int i = 0; i < m; ++i) {
        int u, v;
        if(i == 0) {
            u = a1;
            v = a2;
        } else {
            // Generate next two numbers in the sequence
            // next_val1 represents a_{2i+1} roughly (the first element of the pair)
            int next_val1 = (x * seq_prev2 + y * seq_prev1 + z) % n;
            seq_prev2 = seq_prev1;
            seq_prev1 = next_val1;
            
            // next_val2 represents a_{2i+2} roughly (the second element of the pair)
            int next_val2 = (x * seq_prev2 + y * seq_prev1 + z) % n;
            seq_prev2 = seq_prev1;
            seq_prev1 = next_val2;
            
            // Apply the modification rule for u
            u = (next_val1 + v_last) % n;
            v = next_val2;
        }
        
        v_last = tree.lca(u, v);
        total_sum += v_last;
    }

    cout << total_sum << ln;
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