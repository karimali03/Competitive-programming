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

struct RollbackBIT {
    int n;
    vector<int> tree;
    vector<pair<int, int>> history; // Stores {index, value_added}

    RollbackBIT(int sz) : n(sz), tree(sz + 1, 0) {}

    // Add val to index idx
    void add(int idx, int val) {
        history.push_back({idx, val}); // Record for rollback
        for (; idx <= n; idx += idx & -idx) 
            (tree[idx] += val)%=MOD;
    }

    // Prefix sum up to idx
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) 
            (sum += tree[idx])%=MOD;
        return sum;
    }

    // Get range sum [l, r]
    int query(int l, int r) {
        if (l > r) return 0;
        return (query(r) - query(l - 1) + MOD)%MOD;
    }

    
    // Get current state ID
    int snapshot() {
        return history.size();
    }

    // Revert to a previous state ID
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto [idx, val] = history.back();
            history.pop_back();
            // Manually subtract to undo (don't call add() here)
            for (; idx <= n; idx += idx & -idx) 
                tree[idx] = ( tree[idx] - val + MOD )% MOD;
        }
    }
};

int calcLIS(vector<int> & v) { // O( n *  log(n) )
        int n = v.size();
        vector<int>bs(n+1,INT_MAX);
        vii idx(n+1);
        for(int i = 0 ;i < n ;i++){
            int x = lower_bound(bs.begin(),bs.begin()+i+1,v[i]) - bs.begin();
            bs[x] = v[i];
            idx[x].push_back(i);
        }
        int LIS = lower_bound(all(bs),INT_MAX)-bs.begin();
        RollbackBIT bit(n+5);
        vi ans(n);
        sort(all(idx[0]));
        for(auto &it : idx[0]) ans[it] = 1;
        for(int i = 1 ; i < LIS ; i++){
            sort(all(idx[i]));
            int j = 0, sz = idx[i-1].size();
            for(auto &it : idx[i]){
                while(j < sz && idx[i-1][j] < it){
                    bit.add( v[idx[i-1][j]] , ans[idx[i-1][j]]); 
                    j++;
                }
                ans[it] = bit.query(1 , v[it]-1);
            }
            bit.rollback(0);
        }
        int ret = 0;
        for(auto &it : idx[LIS-1]) (ret += ans[it])%=MOD;
        return ret;
}



void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi val = v;
    sort(all(val));
    val.erase(unique(all(val)),val.end());
    for(int i =0 ;i < n;  i++) v[i] = lower_bound(all(val),v[i]) - val.begin() + 1;
    int ans = calcLIS(v);
    cout<<ans<<ln;
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