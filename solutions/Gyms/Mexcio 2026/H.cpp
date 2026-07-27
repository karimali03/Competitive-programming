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



struct IterativeSegmentTree {
    struct node {
        int val, idx;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;
    // Constructor pads size to the next power of 2
    IterativeSegmentTree(int size){
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = node{0, -1};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return a.val > b.val ? a : b;
    }

    // Build array in O(N)
    void build(const vector<int>& a) {
        // Place leaves
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i], i};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Point update: set position pos to new_val in O(log N)
    void update(int pos, int new_val) {
        int original_idx = pos;
        pos += n; // Jump directly to leaf
        tree[pos] = {new_val, original_idx};
        
        // Climb up and update parents
        while (pos >>= 1) {
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    // Query 1: Range query in [l, r] inclusive in O(log N)
    node query1(int l, int r) {
        node resL = neutral, resR = neutral;
        // Convert to half-open interval [l, r+1)
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]); // Merge left side
            if (r & 1) resR = merge(tree[--r], resR); // Merge right side
        }
        return merge(resL, resR);
    }
};

void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n);
    cin>>a>>b;
    IterativeSegmentTree st(100005);
    int cur = -1;
    for(int i = 0;i < n ; i++){
        cur = max( cur+1 , st.query1(1,a[i]).val);
        int steps = cur + a[i] + b[i];
        st.update(a[i] , steps);
    }
    cout<<st.query1(0,100004).val<<ln;
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