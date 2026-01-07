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

const int N = 305;
int dp[N][N][N];
int v[N];
int n;
const int MOD = 1e9+7;
int rec(int i,int mx,int mx2){
    if(i == n) return 1;
    int &ret = dp[i][mx][mx2];
    if(~ret) return ret;
    ret = rec(i+1,mx,mx2);
    if(mx == n+1 || v[i] >= mx) (ret += rec(i+1,v[i],mx2))%=MOD;
    else if(mx2 == n+1 || v[i] >= mx2) (ret += rec(i+1,mx,v[i]))%=MOD;
    return ret;

}
void solve(int test_case) {
    cin>>n;
    f(i,0,n) cin>>v[i];
    f(i,0,n+5) f(j,0,n+5) f(k,0,n+5) dp[i][j][k] = -1;
    int res = rec(0,n+1,n+1);
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