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
int dp1[N],cnt[N],dp2[N];
vector<pair<int,int>>adj[N];
int n;
void rec(int u,int p){
    cnt[u] = 1;
    dp1[u] = 0;
    for(auto [it,w] : adj[u]){
        if(it == p) continue;
        rec(it,u);
        dp1[u] += w * cnt[it] + dp1[it];
        cnt[u]+=cnt[it];
    }
}

void rec2(int u, int p) {
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dp2[v] = dp2[u] + dp1[u] - (dp1[v] + cnt[v] * w) + (n - cnt[v]) * w;

        rec2(v, u);
    }
}
void init(){
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        dp1[i] = dp2[i] = cnt[i] = 0;
    }
}

void solve(int test_case) {
    cin>>n;
    init();
    for(int i = 0 ; i < n-1;i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,1});
        adj[y].push_back({x,1});
    }
    rec(0,-1); rec2(0,-1);
    for(int i = 0;i < n ; i++) cout<<dp1[i]+dp2[i]<<ln;

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