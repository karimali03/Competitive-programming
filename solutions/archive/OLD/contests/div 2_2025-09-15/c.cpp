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

const int MOD = 998244353;
void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;

    vii dp(n,vi(2,-1));
    function<int(int,int)> rec = [&](int i,int j) -> int{
        if(i == n) return 1;
        int &ret = dp[i][j];
        if(~ret) return ret;
        ret = 0;
        pair<int,int> prv = {a[i-1],b[i-1]};
        if(j) prv = {b[i-1],a[i-1]};
        if(prv.first <= a[i] && prv.second <= b[i] ) (ret += rec(i+1,0))%=MOD;
        if(prv.first <= b[i] && prv.second <= a[i]) (ret += rec(i+1,1))%=MOD;
        return ret;
    };
    cout<<(rec(1,1) + rec(1,0))%MOD<<ln;
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