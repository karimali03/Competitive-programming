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


struct SegmentTree {
    struct node {
        vector<int> v;
    };

    int n;
    vector<node> tree;
    node neutral = {{}};
    int sz;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        vector<int> merged;
        int i = 0, j = 0;
        while (i < (int)a.v.size() && j < (int)b.v.size()) {
            if (a.v[i] < b.v[j]) merged.push_back(a.v[i++]);
            else merged.push_back(b.v[j++]);
        }
        while (i < (int)a.v.size()) merged.push_back(a.v[i++]);
        while (j < (int)b.v.size()) merged.push_back(b.v[j++]);
        return {merged};
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {{a[tl]}};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void build(vector<int>&a){
        build(a,0,0,sz-1);
    }

    // Query: count of elements > k in [l, r]
    int query(int l, int r, int k, int v, int tl, int tr) {
        if (l > r) return 0;
        if (l == tl && r == tr) {
            auto bs = upper_bound(tree[v].v.begin(), tree[v].v.end(), k) - tree[v].v.begin();
            return bs;
        }
        int tm = (tl + tr) / 2;
        return query(l, min(r, tm), k, v * 2 + 1, tl, tm) +
               query(max(l, tm + 1), r, k, v * 2 + 2, tm + 1, tr);
    }

    int query(int l,int r,int k){
        return query(l,r,k,0,0,sz-1);
    }
};

vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,n);
    for(int i = 0 ; i < n ; i++){
        while(!st.empty() && v[st.top()] < v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        while(!st.empty() && v[st.top()] <= v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}


void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;
    SegmentTree st(n);
    st.build(b);
    auto ng = NGE(a);
    auto pg = PGE(a);
    vi pre(n);
    auto calc = [&](int l,int r) -> int{
        if(l > r) return 0;
        return pre[r] - l ? pre[l-1] : 0;
    };
    int res = 0;
    for(int i = 0 ; i < n ; i++){
        if(a[i] == b[i]){
            res += (i+1) * (n - i);
            pre[i] = -1 + (i ? pre[i-1] : 0);
        }
    }
    cout<<res<<ln;
    for(int i = 0; i < n ; i++){
        int l = pg[i] + 1;
        int r = ng[i] - 1;
        cout<<a[i]<<" "<<l<<" "<<r<<ln;
        int cnt = st.query(i+1,r,a[i]) + calc(i+1,r);
        res += (i - l + 1) * cnt;
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