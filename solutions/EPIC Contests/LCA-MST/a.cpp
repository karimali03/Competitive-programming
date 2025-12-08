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

const int N = 200005;
const int LOG = 20;
int up[N][LOG];
int par[N],lvl[N];
int dsu[N];
int n;
void add(int p){
    int u = n++;
    dsu[u] = u;
    par[u] = p;
    lvl[u] = lvl[p] + 1;
    up[u][0] = p;
    for(int lg = 1 ; lg < LOG ; lg++){
        up[u][lg] = up[up[u][lg-1]][lg-1];
    }
}

int find(int x){
    if(x == dsu[x]) return x;
    return dsu[x] = find(dsu[x]);
}

int get_kth(int u,int k){
    for(int i = 0;i < LOG;  i++) if((k>>i)&1){
        u = up[u][i];
    }
    return u;
}
int lca(int u,int v){
    if(lvl[u] > lvl[v]) swap(u,v);
    v = get_kth(v,lvl[v]-lvl[u]);
    if(u == v) return u;
    for(int i = LOG-1 ; i >= 0 ; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[v][0];
}

void solve(int test_case) {
    n = 2;
    up[1][0] = 1;
    for(int i = 1 ; i < LOG ; i++) up[1][i] = 1;
    lvl[1] = 0; dsu[1] = 1; par[1] = 1;
    int q; cin>>q;
    while(q--){
        char op; cin>>op;
        if(op == '+'){
            int x; cin>>x;
            add(x);
        }else if(op == '-'){
            int x; cin>>x;
            dsu[x] = dsu[par[x]];
        }else{
            int x,y; cin>>x>>y;
            int lc = find(lca(x,y));
            cout<<lc<<ln;
        }
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