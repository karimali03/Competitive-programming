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
    vi v(2*n); cin>>v;
    vi frq(n,-1);
    for(int i = 0 ; i < 2*n ; i++){
        v[i]--;
        if(frq[v[i]] == -1) frq[v[i]] = i;
    }
    vi dp(2*n);
    dp[0] = 1;
    for(int i = 1;i < 2*n ; i++){
        if(frq[v[i]] != i){
            int len = i - frq[v[i]] + 1;
            dp[i] = len*len;
            if(frq[v[i]]) dp[i] += dp[frq[v[i]]-1];
        }
        dp[i] = max(dp[i] , 1 + dp[i-1]);
    }
    cout<<*max_element(all(dp))<<ln;
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