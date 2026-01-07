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


const int MOD = 1e9+7;

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b/=2;
    }

    return res;
}
void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(q); cin>>v;
    vi dp(n+1);
    vi suf(q+1);
    for(int i = q-1 ; i >= 0 ; i--){
        suf[i] = ((v[i] * fp(fp(2,i+1),MOD-2))%MOD + suf[i+1])%MOD;
    }
    dp[1] = suf[0];
    for(int i = 0 ; i < q ; i++){
        (dp[v[i]] += (fp(2,i) * suf[i+1])%MOD)%=MOD;
    }
    for(int i = 1 ; i <= n ; i++) cout<<dp[i]<<" ";
    cout<<ln;
  //  int res = (6 * fp(8,MOD-2) + 8 * fp(16,MOD-2))%MOD;
  //  cout<<res<<ln;
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