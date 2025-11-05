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

const int MOD = 1e9 + 9;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll BASE = 37;

map<pair<int,int>,int> hval;
int cnt = 1;
ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int get(pair<int,int> x) {
    if (hval.count(x)) return hval[x];
    return hval[x] = mod_pow(BASE, cnt++, MOD);
}

struct MultisetHashing {
    vector<int> h;
    int n;
    MultisetHashing(vector<pair<int,int>> &v) {
        n = v.size();
        h = vector<int>(n + 1);
        for (int i = 0; i < n; i++) {
            (h[i + 1] =  get(v[i]) + h[i])%=MOD;
        }
    }
    // zero based
    int get_hash(int l, int r) {
        int ret = h[r+1] - h[l] + MOD;
        return ret % MOD;
    }
};


void solve(int test_case) {
    int n; cin>>n;
    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].first>>v[i].second;
        if(v[i].first > v[i].second) swap(v[i].first,v[i].second);
    }
    MultisetHashing sh(v);
    map<int,int>mp;
    for(int i = 0;i < n ; i++){
        for(int j = i; j < n ; j++){
            mp[sh.get_hash(i,j)]++;
        }
    }
    int res = 0;
    for(auto &[a,b] : mp) res += (b*(b-1))/2;
    cout<<res<<ln;
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