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
const int N = 200005;
int dp[N][4][3][4];
vii config = {{0,0,0},{0,1,1},{1,0,1},{1,1,0}};
int v[N];
int n;
int rec(int i,int ty,int idx,int len){
    if(i == n) return (len == 3);
    int &ret = dp[i][ty][idx][len];
    if(~ret) return ret;
    ret = rec(i+1,ty,idx,len);
    if( (v[i]%2) == config[ty][idx]) (ret = ret + rec(i+1,ty,(idx+1)%3,min(3ll,len+1)))%=MOD;
    return ret;
};
void solve(int test_case) {
    cin>>n;
    f(i,0,n) cin>>v[i];
    memset(dp,-1,sizeof(dp));
    int res = 0;
    for(int ty = 0 ; ty < 4 ; ty++){
        (res+=rec(0,ty,0,0))%=MOD;
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