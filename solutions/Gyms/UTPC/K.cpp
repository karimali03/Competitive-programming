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
#define pl pair<ll, ll>
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

map<char, pl> C = {
    {'N', {-1, 0}},
    {'S', {1, 0}},
    {'W', {0, -1}},
    {'E', {0, 1}}
};

void solve(int test_case) {
    ll n, m;
    
    cin >> n >> m;

    vector<string> X(n+2, string(n+2, '#'));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> X[i][j];
        }
    }
    string s; cin >> s;


    vector<vii> dp(n+2, vii(n+2, vi(m, -1)));

    function<ll(ll, ll, ll)> dfs = [&](ll i, ll j, ll md) -> ll {
        if (X[i][j] == 'S') return 1;
        if (X[i][j] == '#') return 0;
        ll &ret = dp[i][j][md];
        if (ret == 2) ret = 0;
        if (ret != -1) return ret;
    
        ret = 2;

        auto p = C[s[md]];
        ll ni = i + p.first;
        ll nj = j + p.second;
        if (X[ni][nj] == '#') ret = dfs(i, j, (md+1)%m);
        else ret = dfs(ni, nj, (md+1)%m);

        return ret;
    };

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << dfs(i, j, 0);
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}