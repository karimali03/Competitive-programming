struct SegmentTree {
    struct node {
        int val;
    };

    int n;
    vector<node> tree;
    node neutral = {0};  // Change for different operations

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return {a.val + b.val}; // Change operation if needed
    }

    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query in range [l, r]
    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }

    // Point update at position pos
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = {new_val};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2 + 1, tl, tm, pos, new_val);
            else
                update(v * 2 + 2, tm + 1, tr, pos, new_val);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }


};


