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
    vii adj(n);
    for(int i = 1 ; i < n ; i++){
        int x; cin>>x; adj[x-1].push_back(i);
    }
    int limit,kk;
    function<int(int)> can = [&](int v) -> int{
        if(adj[v].empty()) return 0;
        int cur = 0;
        for(auto it : adj[v]){
            int ret = can(it);
            if(ret == limit-1 && v != 0) kk++;
            else cur = max(cur,1+ret);
        }
        return cur;
    };
    int l = 1 , r = n-1;
    int ans = n-1;
    while(l<=r){
        int h = l + (r-l)/2;
        limit = h , kk = 0;
        can(0);
        if(kk <= k){
            ans = h; r = h-1;
        }else l = h+1;
    }
    cout<<ans<<ln;
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