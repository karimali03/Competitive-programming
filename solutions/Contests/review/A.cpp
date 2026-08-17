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


struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n = 0) : n(n), bit(n + 1) {}

    void add(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    long long sum(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // first index with prefix sum >= k
    int kth(long long k) {
        int pos = 0;

        for (int pw = 1 << __lg(n); pw; pw >>= 1) {
            int nxt = pos + pw;

            if (nxt <= n && bit[nxt] < k) {
                pos = nxt;
                k -= bit[nxt];
            }
        }

        return pos + 1;
    }
};


struct OrderedSum {
    int n;
    BIT cnt, sum;
    vector<long long> val; // val[i] = actual value of compressed index i

    OrderedSum(vector<long long> values)
        : n(values.size()), cnt(n), sum(n), val(n + 1) {

        for (int i = 1; i <= n; i++)
            val[i] = values[i - 1];
    }

    // add/remove occurrence at compressed index i
    // delta = +1 insert, -1 erase
    void add(int i, int delta) {
        cnt.add(i, delta);
        sum.add(i, val[i] * delta);
    }

    // number of existing elements
    long long size() {
        return cnt.sum(n);
    }

    // sum of smallest k existing elements
    long long first_k_sum(long long k) {
        if (k <= 0) return 0;

        int i = cnt.kth(k);

        long long beforeCnt = cnt.sum(i - 1);
        long long beforeSum = sum.sum(i - 1);

        long long need = k - beforeCnt;

        return beforeSum + need * val[i];
    }
};

void solve(int test_case) {
    int n,m; cin>>n>>m;
    vi v(n); cin>>v;
    vi val = v;
    vector<pair<int,int>>op(m);
    for(int i = 0;i < m ; i++){
        cin>>op[i].first>>op[i].second;
        val.push_back(op[i].second);
    }
    sort(all(val));
    val.erase(unique(all(val)),val.end());
    OrderedSum st(val);
    for(int i = 0;i <n ; i++){
        int idx = lower_bound(all(val),v[i]) - val.begin() + 1;
        st.add(idx,1);
    }
    for(int i =0 ;i < m ; i++){
        auto [a,b] = op[i];
        cout<<st.first_k_sum(a)<<" ";
        int prv = st.cnt.kth(a);
        int idx = lower_bound(all(val),b) - val.begin() + 1;
        st.add(prv,-1);
        st.add(idx,1);
    }
    cout<<ln;
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