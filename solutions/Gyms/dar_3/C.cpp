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




struct SparseTable {
    vector<vector<int>> val;
    int n,lg;

    SparseTable(const vector<int>& v) {
        n = v.size();
        if (n == 0) return;
        // 31 - __builtin_clz(n) + 1
        lg = std::__lg(n) + 1; 
        val.assign(lg, vector<int>(n));
        for (int i = 0; i < n; i++) {
            val[0][i] = v[i];
        }
        // Build the table
        for (int k = 1; k < lg; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                val[k][i] = val[k - 1][i] |  val[k - 1][i + (1 << (k - 1))];
            }
        }
    }

    // O(1) query
    int query(int L, int R) {
        int k = std::__lg(R - L + 1);
        return val[k][L] | val[k][R - (1 << k) + 1];
    }

    int query_log(int L, int R){
        int ans = 2e9; 
        for (int k = lg - 1; k >= 0; k--) {
            if ((1 << k) <= R - L + 1) {
                ans = min(ans, val[k][L]); 
                L += (1 << k);           
            }
        }
        return ans;
    }
};


void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    ll res = 0;
    auto spt = SparseTable(v);
    vi pre(n);
    map<int,vi>mp;
    for(int i = 0;i < n ; i++){
        pre[i] = v[i];
        if(i) pre[i]^=pre[i-1];
        mp[pre[i]].push_back(i);
    }
    int prv = 0;
    for(int i = 0;i < n ; i++){
        int cur = v[i];
        int r = i;
        while(r < n){
            int nr = r;
            for(int lg = spt.lg-1 ; lg >= 0 ; lg--){
                if(nr + (1<<lg) <= n){
                    if((cur|spt.val[lg][nr]) == cur){
                        nr += (1 << lg);
                    }
                }
            }
           
            int val = prv^cur;
            if(mp.count(val)){
                res += upper_bound(all(mp[val]),nr-1) - lower_bound(all(mp[val]),r);
            }
            r = nr;
            if(r < n) cur |= v[r];
        }
        prv = pre[i];
    }
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