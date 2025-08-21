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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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

// The number of ways to put n identical objects into k labeled boxes  
int starsAndBars(int n, int k) {
    if (n < 0 || k <= 0) return 0;
    return nCr(n + k - 1, n);
}


void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    int res = 0;
    for(int i = 1 ; i <= n ; i++){
        int cur = (k%MOD * fp(k-1,i-1))%MOD;
        cur = (cur%MOD * nCr(n-1,i-1)%MOD)%MOD;
        cur = (cur%MOD * starsAndBars(i,m)%MOD)%MOD;
        cur = (cur%MOD * fp(m,n-i)%MOD)%MOD;
        (res+=cur)%=MOD;
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