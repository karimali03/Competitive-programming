struct SegmentTree {
    struct node {
        long long sum, pref, suff, ans;
        int len;      // We must track length for range assignments
        bool is_null; // Identifies our neutral element
    };

    int n, h;
    vector<node> tree;
    vector<long long> lazy;
    vector<bool> has_lazy; // Boolean flag to distinguish "set to 0" from "no update"
    node neutral;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        h = __builtin_ctz(n);
        
        neutral = {0, 0, 0, 0, 0, true};
        tree.assign(2 * n, neutral);
        lazy.assign(n, 0);
        has_lazy.assign(n, false);
    }

    node merge(const node &l, const node &r) {
        if (l.is_null) return r;
        if (r.is_null) return l;

        node res;
        res.is_null = false;
        res.len = l.len + r.len;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans = max({l.ans, r.ans, l.suff + r.pref});
        return res;
    }

    // Apply a "Set to X" operation to a node
    void apply(int p, long long val) {
        tree[p].sum = (long long)tree[p].len * val;
        
        // If val >= 0, we take the whole segment. If val < 0, we take just one element.
        long long max_val = max(val, tree[p].sum); 
        tree[p].pref = tree[p].suff = tree[p].ans = max_val;

        if (p < n) {
            lazy[p] = val;
            has_lazy[p] = true;
        }
    }

    // Push pending assignments from root down to parents of p
    void push_path(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (has_lazy[i]) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                has_lazy[i] = false;
            }
        }
    }

    // Rebuild the tree bottom-up from p to root
    void build_up(int p) {
        while (p > 1) {
            p >>= 1;
            // Recalculate based on children
            tree[p] = merge(tree[p << 1], tree[p << 1 | 1]);
            
            // If this node currently has an unpushed lazy tag of its own, 
            // that tag overwrites the merged result from its children.
            if (has_lazy[p]) {
                tree[p].sum = (long long)tree[p].len * lazy[p];
                long long max_val = max(lazy[p], tree[p].sum);
                tree[p].pref = tree[p].suff = tree[p].ans = max_val;
            }
        }
    }

    // Build the initial tree in O(N)
    void build(const vector<long long>& a) {
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i], a[i], a[i], a[i], 1, false};
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Range Set: Set all elements in [l, r] inclusive to `val`
    void update_range(int l, int r, long long val) {
        l += n; r += n + 1; // Half-open interval [l, r+1)
        int l0 = l, r0 = r;

        push_path(l0); 
        push_path(r0 - 1);

        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }

        build_up(l0); 
        build_up(r0 - 1);
    }

    // Query: Get max subarray data in [l, r] inclusive
    node query(int l, int r) {
        l += n; r += n + 1;
        
        // Push tags to ensure fresh data at our query bounds
        push_path(l); 
        push_path(r - 1);
        
        node resL = neutral, resR = neutral;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]);
            if (r & 1) resR = merge(tree[--r], resR);
        }
        return merge(resL, resR);
    }
};
