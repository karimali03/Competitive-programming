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
vector<int> g[N];
int sz[N],lvl[N]{};
bool cut[N];
int par[N];
int dist[N][20];
int mn[N]; 

int get_sz(int x,int p){
    sz[x] = 1;
    for(auto &it : g[x]){
        if(it == p || cut[it]) continue;
        sz[x] += get_sz(it,x);
    }
    return sz[x];
}

int get_centroid(int x,int p,int tot){
    for(auto &it : g[x]){
        if(it == p || cut[it]) continue;
        if(sz[it] * 2 > tot) return get_centroid(it,x,tot);
    }
    return x;
}


void add(int x,int p){
    if(~p){
        par[x] = p;
        lvl[x] = 1 + lvl[p];
    }else{
        par[x] = -1;
        lvl[x] = 0;
    }
}
void calc(int x,int p,int d,int cur){
    dist[x][cur] = d;
    for(auto &it : g[x]){
        if(it == p || cut[it]) continue;
        calc(it,x,d+1,cur);
    }
}
void decompose(int x,int p){
    // get centroid
    int cen = get_centroid(x,-1,get_sz(x,-1));
    add(cen,p);
    calc(cen,-1,0,lvl[cen]);
    cut[cen] = true;
    // make next centroids
    for(auto &it : g[cen]) if(!cut[it]) decompose(it,cen);
}


void upd(int x){
    int r = x;
    while(~x){
        mn[x] = min(mn[x] , dist[r][lvl[x]]);
        x = par[x];
    }
}

int get(int x){
    int ret = 1e9;
    int cur = x;
    while(~x){
        ret = min(ret , dist[cur][lvl[x]] + mn[x]);
        x = par[x];
    }
    return ret;
}
void solve(int test_case) {
    int n,m; cin>>n>>m;
    fill(mn,mn+n,1e9);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    decompose(0,-1);
    upd(0);
    while(m--){
        int a,b; cin>>a>>b; b--;
        if(a == 1){
            upd(b);
        }else{
            cout<<get(b)<<ln;
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