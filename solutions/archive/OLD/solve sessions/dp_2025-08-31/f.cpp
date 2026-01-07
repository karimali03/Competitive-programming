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

const int N = 3005;
int dp[N][N]{};

const int MOD = 1e9+7;
void solve(int test_case) {
    int n; cin>>n;
    string s; cin>>s;
    dp[0][1] = 1;
    for(int i = 1 ; i < n ; i++){
        for(int x = 1 ; x < n ; x++) (dp[i-1][x] += dp[i-1][x-1])%=MOD;
        for(int prv = 1 ; prv <= i+1 ; prv++){
            if(s[i-1] == '<'){
                dp[i][prv] = (dp[i-1][prv-1] - dp[i-1][0] + MOD)%MOD;
            }else{
                dp[i][prv] = (dp[i-1][i] - dp[i-1][prv-1] + MOD)%MOD;
            }
        }
    }
    int res = 0;
    for(int i = 1 ; i <= n ; i++) (res+=dp[n-1][i])%=MOD;
    cout<<res<<ln;
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