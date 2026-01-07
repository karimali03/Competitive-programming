// Helper: Calculate Sum of AP Series
// Sum = n/2 * (2*a + (n-1)*d)
int get_ap_sum(int a, int d, int n) {
    return n * a + (n * (n - 1) / 2) * d;
}

struct SegmentTree {
    struct node {
        int val;
    };
    struct lzy {
        int a, d;
    };
    vector<node> tree;
    vector<lzy> lazy;
    
    int n;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, {0});
        lazy.resize(2 * n, {0, 0});
    }

    // 1. Applies lazy to CURRENT node (fixes the stale value)
    // 2. Pushes lazy to children
    // 3. Clears lazy
    void push(int v, int tl, int tr) {
        // If no lazy, do nothing
        if (lazy[v].a == 0 && lazy[v].d == 0) return;

        int len = tr - tl + 1;
        
        tree[v].val += get_ap_sum(lazy[v].a, lazy[v].d, len);

        // 2. Push to children (if not leaf)
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            int left = 2 * v + 1;
            int right = 2 * v + 2;

            // Pass to Left Child
            lazy[left].a += lazy[v].a;
            lazy[left].d += lazy[v].d;

            // Pass to Right Child
            int dist = (tm + 1) - tl;
            int start_r = lazy[v].a + dist * lazy[v].d;
            lazy[right].a += start_r;
            lazy[right].d += lazy[v].d;
        }

        // 3. Clear current lazy
        lazy[v] = {0, 0};
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v].val = tree[v * 2 + 1].val + tree[v * 2 + 2].val;
        }
    }
    
    void build(vector<int> &a) {
        build(a, 0, 0, n - 1);
    }

    void update(int v, int tl, int tr, int l, int r, int a, int d) {
        push(v, tl, tr);
        if (l > r) return;
        
        if (l == tl && r == tr) {
            lazy[v].a += a;
            lazy[v].d += d;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), a, d);
            int dist = max(l, tm + 1) - l;
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, a + dist * d, d);
            tree[v].val = tree[v * 2 + 1].val + tree[v * 2 + 2].val;
        }
    }
    
    void update(int l, int r) {
        update(0, 0, n - 1, l, r, 1, 1);
    }

    int query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v].val;
        
        int tm = (tl + tr) / 2;
        return query(v * 2 + 1, tl, tm, l, min(r, tm)) +
               query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
    }
    
    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

