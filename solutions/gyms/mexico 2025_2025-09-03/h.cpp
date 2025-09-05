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

const int N = 100005;
const int MOD = 1e9+7;
int dp[N][65][2];
int n,m; 
string x,y;
int rec(int i,int j,int ch){
    if(j == m) return (ch ? 1 : (25 * (n-m) + 1) % MOD);
    if(i == n) return 0;
    int &ret = dp[i][j][ch];
    if(~ret) return ret;
    ret = rec(i+1,j,ch);
    if(x[i] == y[j]) (ret+=rec(i+1,j+1,ch))%=MOD;
    else if(!ch) (ret += rec(i+1,j+1,1))%=MOD;
    return ret;
}
void solve(int test_case) {
    cin>>n>>m;
    cin>>x>>y;
    memset(dp,-1,sizeof(dp));
    cout<<rec(0,0,0)<<ln;
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