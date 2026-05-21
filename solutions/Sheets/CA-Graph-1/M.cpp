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

#define loop(u,e,v) for (int e = head[u], v; ~e && (v = to[e], 1); e = nxt[e])
const int N = 1000005;
const int M = 2000005;
int head[N],to[M],nxt[M],ne;
void init(int n){
    ne = 0;
    memset(head,-1,n*sizeof(head[0]));
}
void add(int u,int v,int w = 0){
    to[ne] = v;
    nxt[ne] = head[u];
    head[u] = ne++;
}


void solve(int test_case) {
    int n; cin>>n;
    init(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        add(x,y); add(y,x);
    }    
    vi vis(n);
    int mx = 0 , idx = 0;
    function<void(int,int)> dfs = [&](int x,int p){
        vis[x] = 1;
        int c = p;
        loop(x,e,y){
            if(vis[y]) continue;
            c++;
            dfs(y,1);
        }
        if(c > mx) mx = c , idx = x;
    };
    dfs(0,0);
    int cc = mx;
    vis = vi(n);
    vis[idx] = 1;
    mx = 0;
    f(i,0,n) if(!vis[i]) dfs(i,0);
    cc += mx-1;
    cout<<cc<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}