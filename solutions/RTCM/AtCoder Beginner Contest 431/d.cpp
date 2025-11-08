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

const int N = 505;
const int MX = 505*505;
int W[N];
int H[N],B[N];
int n;
int dp[N][MX];
int tot;

void solve(int test_case) {
    cin>>n;
    tot = 0;
    for(int i =0;i<n;i++){
        cin>>W[i]>>H[i]>>B[i];
        tot+=W[i];
    }
    for(int i = 0 ; i < MX; i++){
        if(i > tot-i) dp[n][i] = -1e16;
        else dp[n][i] = 0;
    }

    for(int i = n-1 ; i >= 0 ; i--){
        for(int sum = tot ; sum >= 0 ; sum--){
            int ret = dp[i+1][sum] + B[i];
            ret = max(ret , H[i] + dp[i+1][sum+W[i]]);
            dp[i][sum] = ret;
        }
    }
    cout<<dp[0][0]<<ln;
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