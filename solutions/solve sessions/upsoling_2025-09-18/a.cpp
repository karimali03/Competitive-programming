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

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    void add(int idx, ll val){ // idx is 1..n
        while(idx <= n){
            bit[idx] = (bit[idx] + val) % MOD;
            idx += idx & -idx;
        }
    }
    ll sumPrefix(int idx){ // sum 1..idx
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]) % MOD;
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1) + MOD) % MOD;
    }
};

void solve(){
        int n; cin >> n;
        vector<Fenwick>row(n+1,Fenwick(n+2));
        vector<Fenwick>col(n+1,Fenwick(n+2));
        row[0].add(1,1); col[0].add(1,1);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            vi a(n+1), b(n+1);

            // Case 1: x becomes new second maximum
            for (int m = x+1; m <= n; m++) {
                a[m] = row[m].sumPrefix(x+1);  // old sm ≤ x
            }

            // Case 2: x becomes new maximum
            for (int sm = 0; sm < x; sm++) {
                b[sm] = col[sm].sumPrefix(x+1);  // old max ≤ x
            }

            // Update transitions
            for (int m = x+1; m <= n; m++) {
                if (a[m]) col[x].add(m+1, a[m]); // state (max=m, sm=x)
            }
            for (int sm = 0; sm < x; sm++) {
                if (b[sm]) row[x].add(sm+1, b[sm]); // state (max=x, sm=sm)
            }
        }
        int res = 0;
        for (int m = 0; m <= n; m++) {
            res = (res + row[m].sumPrefix(n+1)) % MOD;
        }
        cout << res << ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve();
    }

    return 0;
}