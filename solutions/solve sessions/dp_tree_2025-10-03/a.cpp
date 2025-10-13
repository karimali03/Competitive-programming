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
    int n; cin>>n;
    vector<vector<pair<int,int>>>v(n);
    for(int i = 1; i  < n; i++){
        int x,y; cin>>x>>y; x--,y--;
        v[x].push_back({y,0});
        v[y].push_back({x,1});
    }   
    vi dp(n);
    function<int(int,int)> rec = [&](int x,int p) -> int{
        for(auto [a,b] : v[x]){
            if(a == p) continue;
            dp[x] += rec(a,x) + b;
        }
        return dp[x];
    };
    rec(0,-1);
    int ans = n-1;
    vi op;
    function<void(int,int)> reroot = [&](int x,int p){
        if(dp[x] <  ans){
            op.clear(); ans = dp[x]; op.push_back(x);
        }
        else if(dp[x] == ans) op.push_back(x);
    
        for(auto [a,b] : v[x]){
            if(a == p) continue;
            // make a the root
            int prev = dp[x];
            dp[x] =  dp[x] - dp[a] - b;
            dp[a] = dp[a] + dp[x] + (1-b);
            reroot(a,x);
            // return x the root
            dp[x] = prev;
        }
    };
    reroot(0,-1);
    cout<<ans<<ln;
    sort(all(op));
    for(auto it : op) cout<<it+1<<" ";
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