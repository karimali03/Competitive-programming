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
const int MOD = 1e9+9;
int dp[N][10][10][2];
vector<int>prime(N,1);
int C[10][10][10]{};
void solve(int test_case) {
    int n; cin>>n;
    memset(dp,-1,sizeof(dp));
    function<int(int,int,int,int)> rec = [&](int i,int c1,int c2,int vld) -> int{
        if(i == n) return vld;
        int &ret = dp[i][c1][c2][vld];
        if(~ret) return ret;
        ret = 0;
        for(int ch = 0; ch <= 9 ; ch++) (ret += rec(i+1,c2,ch,vld | C[c1][c2][ch]))%=MOD;
        return ret;
    };
    int ans = 0;
    for(int d1 = 1 ; d1 <= 9 ; d1++){
        for(int d2 = 0 ; d2 <= 9 ; d2++){
            (ans += rec(2,d1,d2,0))%=MOD;
        }
    }
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for(int i = 2 ; i*i <= 1000 ; i++){
        if(prime[i]){
            for(int j=i*i ; j <= N ; j+=i) prime[j] = 0;
        }
    }
    for(int i = 100 ; i < 1000 ; i++) if(prime[i]){
        int num = i;
        int c = num%10; num/=10;
        int b = num%10; num/=10;
        int a = num%10;
        C[a][b][c] = 1;
    }
    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}