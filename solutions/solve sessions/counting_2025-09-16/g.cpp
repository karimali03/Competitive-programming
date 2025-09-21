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


const int N = 1'000'005;
const int MOD = 998244353;
int fact[N], inv_fact[N];

int fp(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void INIT() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < N; i++) 
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    for (int i = 1; i < N; i++) 
        inv_fact[i] = fp(fact[i], MOD - 2);
}

int nCr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int nPr(int n, int r) {
    if (n < r || r < 0) return 0;
    return 1LL * fact[n] * inv_fact[n - r] % MOD;
}

int catalan(int n) {
    if (n == 0) return 1;
    int res = nCr(2 * n, n);
    res = 1LL * res * fp(n + 1, MOD - 2) % MOD;
    return res;
}

// 1. Identical balls, distinct boxes, empty allowed
int starsAndBars(int balls, int boxes) {
    if (balls < 0 || boxes <= 0) return 0;
    return nCr(balls + boxes - 1, boxes - 1);
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    map<int,int>mp;
    f(i,0,n) mp[v[i]]++;
    int mx = mp.rbegin()->first;
    if(mp[mx] > 1 || mp.size() == 1){
        cout<<fact[n]<<ln; return;
    }
    if(!mp.count(mx-1)){
        cout<<0<<ln;
        return;
    }

    int res = fact[n];
    if(mp.rbegin()->second == 1){
         int c = next(mp.rbegin())->second;
        for(int i = c ; i < n ; i++){
            int cur = ((nCr(n-c-1,i-c) * fact[i])%MOD * fact[n - i - 1])%MOD;
            res = (res - cur + MOD)%MOD;
        }
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    INIT();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}