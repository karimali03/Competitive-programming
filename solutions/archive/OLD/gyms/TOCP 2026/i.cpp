#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define vi vector<int>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define int long long

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

// ---------------------- Segment Tree 2 ----------------------
struct SegmentTree2 {
    struct node {
        int val, vld;
    };
    
    vector<node> tree;
    vector<int> lazy;
    node neutral = {0, 0};
    int no_operation = 0;
    int sz, n;

    SegmentTree2(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        return {a.val + b.val, a.vld + b.vld};
    }

    // Optimization: Standard O(1) push
    void push(int v, int tl, int tr) {
        if (lazy[v] != no_operation) {
            tree[v].val += tree[v].vld * lazy[v];
            if (tl != tr) {
                lazy[v * 2 + 1] += lazy[v];
                lazy[v * 2 + 2] += lazy[v];
            }
            lazy[v] = no_operation;
        }
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(query(v * 2 + 1, tl, tm, l, min(r, tm)),
                     query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
    }
    node query(int l, int r) { return query(0, 0, sz - 1, l, r); }

    void update(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v]++;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm));
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int l, int r) { update(0, 0, sz - 1, l, r); }

    void update2(int v, int tl, int tr, int idx) {
        push(v, tl, tr);
        if (tl == tr) {
            tree[v].vld = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (idx <= tm) update2(v * 2 + 1, tl, tm, idx);
            else update2(v * 2 + 2, tm + 1, tr, idx);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update2(int idx) { update2(0, 0, sz - 1, idx); }
};

// ---------------------- Segment Tree 1 ----------------------
struct SegmentTree {
    struct node {
        int val, idx, cnt;
    };
    
    vector<node> tree;
    vector<int> lazy;
    // Use a very small number for safety instead of complex calculation
    node neutral = {(int)-1e16, -1, 0}; 
    int no_operation = 0;
    int sz, n;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        if (a.val > b.val) return {a.val, a.idx, a.cnt + b.cnt};
        return {b.val, b.idx, a.cnt + b.cnt};
    }

    // Optimization: Standard O(1) push
    void push(int v, int tl, int tr) {
        if (lazy[v] != no_operation) {
            tree[v].val += lazy[v];
            if (tl != tr) {
                lazy[v * 2 + 1] += lazy[v];
                lazy[v * 2 + 2] += lazy[v];
            }
            lazy[v] = no_operation;
        }
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl], tl, 0};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void build(vector<int> &a) { build(a, 0, 0, sz - 1); }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(query(v * 2 + 1, tl, tm, l, min(r, tm)),
                     query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
    }
    node query(int l, int r) { return query(0, 0, sz - 1, l, r); }

    void update(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v] += x;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), x);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int l, int r, int x) { update(0, 0, sz - 1, l, r, x); }

    // Optimization: Combined "Modify" function.
    // Handles finding the leaf, updating cnt, and resetting val in ONE pass.
    // Returns true if the number became 1 (so we can update ST2).
    bool modify(int v, int tl, int tr, int idx, int &p_val) {
        push(v, tl, tr);
        if (tl == tr) {
            // Logic moved from main loop to here
            tree[v].cnt++;
            p_val = max(1ll, p_val / 2);
            
            if (p_val == 1) {
                tree[v].val = -1e15; // Effectively remove from ST1 consideration
                return true;
            } else {
                // Reset value: 1e6 - p[i]. This removes accumulated lazy.
                tree[v].val = 1000000 - p_val;
                return false;
            }
        }
        int tm = (tl + tr) / 2;
        bool res;
        if (idx <= tm) res = modify(v * 2 + 1, tl, tm, idx, p_val);
        else res = modify(v * 2 + 2, tm + 1, tr, idx, p_val);
        
        tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        return res;
    }
    bool modify(int idx, int &p_val) { return modify(0, 0, sz - 1, idx, p_val); }
};


void solve(int test_case) {
    int n, q; cin >> n >> q;
    vi p(n); cin >> p;
    vi base(n);
    f(i, 0, n) base[i] = 1000000 - p[i];
    
    // Declare ST2 before ST1 for clarity
    SegmentTree2 s(n);
    SegmentTree st(n);
    
    st.build(base);
    
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int l, r, k; cin >> l >> r >> k; l--, r--;
            st.update(l, r, k);
            s.update(l, r);
            
            // Query once
            auto cur = st.query(l, r);
            
            // Loop still exists (as requested), but body is much faster
            while(cur.val >= 1000000) {
                // Optimization: Single function call to update ST1 logic
                // Pass p[cur.idx] by reference to update it
                bool became_one = st.modify(cur.idx, p[cur.idx]);
                
                if (became_one) {
                    s.update2(cur.idx);
                }
                
                // Fetch next candidate
                cur = st.query(l, r);
            }
        } else {
            int l, r; cin >> l >> r; l--, r--;
            int res = st.query(l, r).cnt + s.query(l, r).val;
            cout << res << ln;
        }
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