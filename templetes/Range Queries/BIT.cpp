struct BIT {
    int n;
    vector<int> tree;

    BIT(int size) {
        n = size;
        tree.assign(n + 1, 0); 
    }

    void update(int i, int delta) {
        i++; 
        while (i <= n) {
            tree[i] += delta;
            i += i & -i;
        }
    }

    // Get prefix sum [0..i] (0-indexed)
    int query(int i) {
        i++; 
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }

    // Range sum [l..r] (both 0-indexed)
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Set value at index i (0-indexed)
    void set(int i, int new_val) {
        int curr = range_query(i, i);
        update(i, new_val - curr);
    }
};

