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

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi a(n); cin>>a;
    int sum =0;
    f(i,0,n) sum += a[i];
    vector<vector<pair<int,int>>> g(n);
    for(int i = 1;i < n ; i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }   
    if(sum%k){
        NA;
        return;
    }
    int res = 0;
    function<int(int,int)> dfs = [&](int x,int p) -> int{
        int ret = a[x];
        for(auto &[it,w] : g[x]) if(it != p){
            int cur = dfs(it,x);
            res += min(cur , k - cur) * w;
            (ret += cur)%=k;
        }
        return ret % k;
    };
    dfs(0,-1);
    cout<<res<<ln;
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