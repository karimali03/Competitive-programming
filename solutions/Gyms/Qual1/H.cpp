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

const int MOD = 1e9 + 7;

struct Element {
    long long w, val;
    bool operator<(const Element& other) const {
        return w < other.w; 
    }
};

struct Node {
    vector<Element> elements;
    vector<long long> pref_prod; // 1-indexed prefix products of 'val'
};

struct MergeSortTree {
    int n;
    vector<Node> tree;

    MergeSortTree(const vector<Element>& a) {
        n = a.size();
        tree.resize(2 * n);
        
        // Build leaves
        for (int i = 0; i < n; i++) {
            tree[n + i].elements = {a[i]};
            // We accumulate 'val' in the product
            long long v = a[i].val % MOD;
            if (v < 0) v += MOD; 
            tree[n + i].pref_prod = {1, v};
        }
        
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; i--) {
            const Node& left = tree[i << 1];
            const Node& right = tree[i << 1 | 1];
            
            tree[i].elements.resize(left.elements.size() + right.elements.size());
            merge(left.elements.begin(), left.elements.end(),
                  right.elements.begin(), right.elements.end(),
                  tree[i].elements.begin());
            
            int sz = tree[i].elements.size();
            tree[i].pref_prod.resize(sz + 1);
            tree[i].pref_prod[0] = 1;
            for (int j = 0; j < sz; j++) {
                long long v = tree[i].elements[j].val % MOD;
                if (v < 0) v += MOD;
                tree[i].pref_prod[j + 1] = (tree[i].pref_prod[j] * v) % MOD;
            }
        }
    }


    long long query(int l, int r, long long max_w) {
        long long res = 1;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = (res * get_segment_prod(tree[l++], max_w)) % MOD;
            }
            if (r & 1) {
                res = (res * get_segment_prod(tree[--r], max_w)) % MOD;
            }
        }
        return res;
    }

private:
    long long get_segment_prod(const Node& node, long long max_w) {
        Element dummy = {max_w, 0};
        auto it = upper_bound(node.elements.begin(), node.elements.end(), dummy);
        int count = distance(node.elements.begin(), it);
        return node.pref_prod[count]; 
    }
};

int fp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = a * res % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve(int test_case) {
    int n, q; cin >> n >> q;
    vi val(n); cin >> val;
    vi w(n); cin >> w;
    vii g(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y; x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }   
    vi in(n, -1);
    vi out(n, -1);
    int timer = -1;
    function<void(int, int)> dfs = [&](int x, int p) {
        in[x] = ++timer;
        for (auto &it : g[x]) if (it != p) dfs(it, x);
        out[x] = timer;
    };
    dfs(0, -1);
    
    vector<Element> res(n);
    for (int i = 0; i < n; i++) {
        res[in[i]] = {w[i], val[i]};
    }
    MergeSortTree st(res);
    while (q--) {
        int u, l, r; cin >> u >> l >> r; u--;
        auto a = st.query(in[u], out[u], r);
        auto b = st.query(in[u], out[u], l - 1);
        int cur = (a * fp(b, MOD - 2)) % MOD;
        cout << cur << ln;
    }
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