struct SegmentTree {
    struct node {
        vector<int> v;
    };

    int n;
    vector<node> tree;
    node neutral = {{}};

    SegmentTree(int size) {
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

    void build(const vector<int> &a, int v = 0, int tl = 0, int tr = -1) {
        if (tr == -1) tr = (int)a.size() - 1;
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {{a[tl]}};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query: count of elements > k in [l, r]
    int query(int l, int r, int k, int v = 0, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;
        if (l > r) return 0;
        if (l == tl && r == tr) {
            auto bs = upper_bound(tree[v].v.begin(), tree[v].v.end(), k) - tree[v].v.begin();
            return tree[v].v.size() - bs;
        }
        int tm = (tl + tr) / 2;
        return query(l, min(r, tm), k, v * 2 + 1, tl, tm) +
               query(max(l, tm + 1), r, k, v * 2 + 2, tm + 1, tr);
    }
};
