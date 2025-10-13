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


bool chk(int ch, int n, vi& v) {
    vi C(n);
    C[0] = ch;
    f(i, 1, n) {
     
        C[i] = (v[i] - v[i-1] + 1) - C[i-1];
        if (C[i] < 0 || C[i] > 1)  return false; 
    }
    int r = 0;
    for (int x : C) {
        if (x == 0) r++;
    }
    int ret = C[0] + r;
    return ret == v[0];
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    if(n == 1){
        if(v[0] == 1) cout << 2 << ln;
        else cout << 0 << ln;
        return;
    }

    int ans = 0;
    if (chk(1, n, v)) ans++;
    if (chk(0, n, v))  ans++;
    cout << ans << ln;
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