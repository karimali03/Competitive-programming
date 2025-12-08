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