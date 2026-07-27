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


const int N = 20;
int dp[1<<N][N][2];
array<int,4> v[N];
int C[N][N][2][2];
int len[N];
int L[N],R[N];
void solve(int test_case) {
    int n; cin>>n;
    for(int i = 0;i < n ; i++){
        for(int j = 0; j< 4 ; j++) cin>>v[i][j];
        v[i][0] *= -1;
        v[i][2] *= -1;
        len[i] = max(v[i][1],v[i][3]) - min(v[i][0],v[i][2]);
        L[i] = abs(v[i][0]-v[i][2]);
        R[i] = abs(v[i][1]-v[i][3]);
    }
    for(int i = 0;i < n ; i++){
        for(int j = 0;j < n ; j++){
            C[i][j][0][0] = len[j] - min(R[i],L[j]);
            C[i][j][1][0] = len[j] - min(L[i],L[j]);
            C[i][j][0][1] = len[j] - min(R[i],R[j]);
            C[i][j][1][1] = len[j] - min(L[i],R[j]);
        }
    }


    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i][0] = 1e18;
            dp[mask][i][1] = 1e18;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[1 << i][i][0] = len[i];
        dp[1 << i][i][1] = len[i];
    }

    // mask i 0/1
    for(int mask=1;mask<(1<<n);mask++){
        for(int i=0;i<n;i++){
            if(!((mask>>i)&1)) continue;
            for(int j = 0; j < n ; j++){
                if((mask>>j)&1) continue;
                int nm = mask | (1<<j);
                int opt0 = min(dp[mask][i][0] + C[i][j][0][0],dp[mask][i][1] + C[i][j][1][0]);
                int opt1 = min(dp[mask][i][0] + C[i][j][0][1],dp[mask][i][1] + C[i][j][1][1]);
                dp[nm][j][0] = min(dp[nm][j][0],opt0);
                dp[nm][j][1] = min(dp[nm][j][1],opt1);
            }
        }
    }

    int res = 1e18;
    for(int i = 0;i < n ; i++){
        res = min({res , dp[(1<<n)-1][i][0] , dp[(1<<n)-1][i][1]});
    }
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