struct SegmentTree {
    struct node {
        vi v;
    };

    int n;
    vector<node> tree;
    node neutral = { {INT_MIN} };  // Change for different operations

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        vi merged;
        int i = 0 , j = 0 , k = 0;
        while(i < a.v.size() && j < b.v.size()){
            if(a.v[i] < b.v[j])  merged.push_back(a.v[i++]);
            else merged.push_back(b.v[j++]);
        }
        while(i < a.v.size()) merged.push_back(a.v[i++]);
        while(j < b.v.size()) merged.push_back(b.v[j++]);

        return { merged };
    }

    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = { {a[tl]} };
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query in range [l, r]
    int query(int v, int tl, int tr, int l, int r , int k) {
        if (l > r) return 0;
        if (l == tl && r == tr){
            auto bs = upper_bound(all(tree[v].v) , k) - tree[v].v.begin();
            return tree[v].v.size() - bs;
        }
        int tm = (tl + tr) / 2;
        auto left = query(v * 2 + 1, tl, tm, l, min(r, tm) , k);
        auto right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r , k);
        return left + right;
    }

};
