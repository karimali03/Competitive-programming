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
const int MOD = 1'000'000'007;
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



void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi vis(n);
    for(int i = 0;i<k;i++){
        int x,y; cin>>x>>y; x--,y--;
        vis[x]= vis[y] = 1;
    }
    int x = count(all(vis),0);
    int res = 0;
    vi calc(x+10);
    calc[0] = calc[1] = 1;
    for(int i = 2 ; i <= x ; i++){
        (calc[i] = calc[i-2] * 2 * (i-1))%=MOD;
    }
    for(int d = (x%2==1) ; d <= x ; d+=2){
        int cur = nCr(x,d);
        int tag = x - d;
        (cur *= calc[tag])%=MOD;
        (res += cur)%=MOD;
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