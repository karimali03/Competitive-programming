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
vector<pair<int,int>>g[N];
const int LOG = 17;
int up[N][LOG];
int val[N][LOG];
int lvl[N];


void init(int n){
    for (int i = 0; i < n; ++i) {
        g[i].clear();
        lvl[i] = 0;
        for (int j = 0; j < LOG; ++j) {
            up[i][j] = 0;
            val[i][j] = 0;
        }
    }
}

int merge(int a,int b){
    return a+b;
}

void dfs(int v,int p){
    for(auto [to,w] : g[v]){
        if(to == p) continue;
        lvl[to] = lvl[v] + 1;
        up[to][0] = v;
        val[to][0] = w;
        for(int j = 1 ; j < LOG; j++){
            up[to][j] = up[up[to][j-1]][j-1];
            val[to][j] = merge(val[to][j-1],val[up[to][j-1]][j-1]);
        }
        dfs(to,v);
    }
}   

void build(int root = 0){
    lvl[root] = 0;
    up[root][0] = root;
    val[root][0] = 0;
    for (int j = 1; j < LOG; ++j) {
            up[root][j] = root;
            val[root][j] = val[root][j-1];
    }
    dfs(root,-1);
}

int lca(int u,int v){
    if (lvl[u] < lvl[v]) swap(u, v);
    int diff = lvl[u] - lvl[v];
    for (int j = LOG - 1; j >= 0; --j)
            if ((diff >> j) & 1)  u = up[u][j];
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j)
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    return up[u][0];   
}

int get_kth(int u,int k){
     for (int j = LOG - 1; j >= 0; --j)
            if ((k >> j) & 1)  u = up[u][j];
    return u;
}

int get_dist(int u, int v){
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
}




void solve(int test_case) {
    int n; cin>>n;
    init(n);
    for(int i=1;i<n;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back({y,1});
        g[y].push_back({x,1});
    }
    int s,t; cin>>s>>t; s--;
    build(s);
    // dimater of every t
    vi dia(n); dia[0] = 0;
    vi dist(n,-1);
    queue<int>q; q.push(s); dist[s] = 0;
    int lvl = 0;
    int a = s,b = s;
    auto calc = [&](int x){
        int d1 = get_dist(a,b);
        int d2 = get_dist(a,x);
        int d3 = get_dist(b,x);
        if(d2 >= d1 && d2 >= d3) b = x;
        else if(d3 >= d1 && d3 >= d2) a = x;
        dia[lvl+1] = get_dist(a,b);
    };
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto cur = q.front(); q.pop();
            for(auto [it,w] : g[cur]) if(dist[it] == -1){
                calc(it);
                dist[it] = 1 + dist[cur];
                q.push(it);
            }
        }
        lvl++;
    }
    for(int i = 1 ; i < n ; i++) dia[i] = max(dia[i] , dia[i-1]);
    int ans = 2 * n;
    vi res(n+1);
    auto get = [&](int time){
        if(time >= n) return dia[n-1];
        return dia[time];
    };
   // cout<<dia<<ln;
    for(int k = 1 ; k <= n ; k++){
        while(k * (ans - t) >= ((get(ans)+1)/2)) ans--;
        res[k] = ans+1;
    }
    f(i,1,n+1) cout<<res[i]<<" ";
    cout<<ln;
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