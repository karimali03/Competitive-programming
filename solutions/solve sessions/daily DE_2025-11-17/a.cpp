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

const int MOD= 998244353;

vi frq;
int n,sh;
int rec(int i,int j,int ch,vii &dp){
    if(j < 0 || j > 2*n) return 0;
    if(i == 0) return j >= sh;
    int &ret = dp[j+sh][ch];
    return  ret;
}

void solve(int test_case) {
    cin>>n;
    frq = vi(n+1);
    for(int i = 0;i < n; i++){
        int x; cin>>x; frq[x]++;
    }
    sort(all(frq));
    sh = n;
    vii dp(2*n+1,vi(2));
    for(int i = sh ; i <= 2*n ; i++) dp[i][0]=dp[i][1] = 1;
    for(int i = 1 ; i <= n ; i++){
        vii cur(2*n+1,vi(2));
        for(int j = 0; j <= 2*n ; j++){
            for(int ch = 0; ch <= 2 ; ch++){
                int ret = 0;
                if(!ch && frq[i]) (ret += rec(i-1,j-frq[i]+sh,1,dp))%=MOD;
                else (ret += rec(i-1,j,ch,dp))%=MOD;
                (ret += frq[i] * rec(i-1,j+frq[i]+sh,ch,dp))%=MOD;
                (cur[j][ch] += ret)%=MOD;
            }
        }
        dp = cur;
    }
    cout<<dp[0][0]<<ln;
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