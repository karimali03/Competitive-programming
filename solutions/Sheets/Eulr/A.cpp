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
void add(int u,int v){
    to[ne] = v;
    nxt[ne] = head[u];
    head[u] = ne++;
}

int deg[N];
int vis[M*2];
int ans[M*2], sz;
int vid = 1;
void eulr(int u){
    for(int v,&e = head[u] ; ~e;) {
        int ee = e;
        e = nxt[e];
        if(vis[ee] == vid) continue;
        vis[ee] = vis[ee ^ 1] = vid;
        v = to[ee];
        eulr(v);
        ans[sz++] = ee;
    }
}

// return true if Eulr path/circuit exists.
// Sets st = valid start node
bool buildEulr(int &st,int m){
    int odd = 0;
    int st = -1;
    for(int i =0 ;i < n ; i++){
        if(deg[i] & 1){ odd++; st = i; }
        if(deg[i] > 0 && st == -1) st = i;
    }
    if(!(odd == 0 || odd == 2)) return false;
    if(st == -1) {sz = 0; return true;}
    sz = 0; ++vid;
    eulr(st);
    if(sz != m) return false;
    reverse(ans , ans + sz);
    return true;
}
// Traverse neighbors of u
// for(int e = head[u] ; ~e ; e = nxt[e]){
//     int v = to[e];
//     int w = wt[e];
// }


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