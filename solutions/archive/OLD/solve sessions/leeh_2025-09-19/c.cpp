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
const int MOD = 998244353;
int dp[N][15];
int dp2[N][15];
int n,k;
int pre(int i,int j);
int rec(int i,int j){
        if(i == n) return (j == k);
        int &ret = dp[i][j];
        if(~ret) return ret;
        ret = rec(i+1,min(k,j+1));
        if(i == 0 || i+2 == n) (ret+=rec(i+2,min(k,j+1)))%=MOD;
        (ret += pre(i+3,min(k,j+1)))%=MOD;
        return ret;
}

int pre(int i,int j){
        if(i >= n+1) return 0;
        int &ret = dp2[i][j];
        if(~ret) return ret;
        return ret = (rec(i,j) + pre(i+1,j))%MOD;
}


void solve(int test_case) {
   cin>>n>>k;
    memset(dp,-1,sizeof(dp));
    memset(dp2,-1,sizeof(dp2));
    cout<<rec(0,0)<<ln;
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