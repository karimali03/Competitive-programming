struct SegmentTree {
    struct node {
        int sum , pref , suf , ans;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;
   

    // Constructor pads size to the next power of 2
    SegmentTree(int size)  {
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = { 0 , 0 ,0 , 0};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return {
            a.sum + b.sum , 
            max(a.pref , a.sum + b.pref),
            max(b.suf , b.sum + a.suf) , 
            max({a.ans , b.ans , a.suf + b.pref})
        };
    }

    // Build array in O(N)
    void build(const vector<int>& a) {
        // Place leaves
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i], a[i] , a[i] , a[i]};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Point update: set position pos to new_val in O(log N)
    void update(int pos, int new_val) {
        pos += n; // Jump directly to leaf
        tree[pos] = {new_val,new_val,new_val,new_val};
        // Climb up and update parents
        while (pos >>= 1) {
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    // Query 1: Range query in [l, r] inclusive in O(log N)
    node query(int l, int r) {
        node resL = neutral, resR = neutral;
        // Convert to half-open interval [l, r+1)
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]); // Merge left side
            if (r & 1) resR = merge(tree[--r], resR); // Merge right side
        }
        return merge(resL, resR);
    }
};
