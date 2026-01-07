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


const int MOD = 1'000'000'007;

int fp(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int q; cin>>q;
    vi cnt(32);
    int res = 0;
    for(int i = 0 ; i < n ; i++){
        for(int b = 0 ; b < 32 ; b++) if((v[i]>>b)&1) cnt[b]++;
    }
    for(int b = 0 ; b < 32 ; b++){
        if(!cnt[b]) continue;
        int cur = ( (fp(2,cnt[b]-1)) * fp(2,n-cnt[b]) ) % MOD;
        if(cnt[b]) cout<<b<<" "<<cur<<ln;
        (cur*=(1ll<<b))%=MOD;
        (res+=cur)%=MOD;
    }
    cout<<res<<ln;
    while(q--){
        int x,y; cin>>x>>y; x--;
    }
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