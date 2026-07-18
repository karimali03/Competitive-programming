struct IterativeSegmentTree {
    struct node {
        int val, idx;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;
    bool mx;

    // Constructor pads size to the next power of 2
    IterativeSegmentTree(int size, bool mx) : mx(mx) {
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = mx ? node{INT32_MIN, -1} : node{INT32_MAX, -1};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        if (mx) return a.val > b.val ? a : b;
        return a.val < b.val ? a : b;
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

    // Helper condition for Query 2 (handles both Max and Min trees)
    bool satisfies_condition(int node_val, int x) {
        if (mx) return node_val >= x; // Finding first element >= x
        else return node_val <= x;    // Finding first element <= x
    }

    // Query 2: Find first index in [l, r] satisfying condition in O(log N)
    pair<int, int> query2(int l, int r, int x) {
        vector<int> left_nodes, right_nodes;
        
        // 1. Gather all canonical nodes that cover [l, r]
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left_nodes.push_back(l++);
            if (r & 1) right_nodes.push_back(--r);
        }

        // Helper lambda to walk down a specific subtree to find the leaf
        auto walk_down = [&](int v) {
            while (v < n) { // While not a leaf
                // If left child satisfies condition, go left
                if (satisfies_condition(tree[v << 1].val, x)) {
                    v = v << 1;
                } else { // Otherwise, it MUST be in the right child
                    v = v << 1 | 1;
                }
            }
            return make_pair(tree[v].val, tree[v].idx);
        };

        // 2. Check left nodes (they are already strictly left-to-right)
        for (int v : left_nodes) {
            if (satisfies_condition(tree[v].val, x)) {
                return walk_down(v);
            }
        }

        // 3. Check right nodes (they were gathered right-to-left, so read backwards)
        for (int i = (int)right_nodes.size() - 1; i >= 0; --i) {
            int v = right_nodes[i];
            if (satisfies_condition(tree[v].val, x)) {
                return walk_down(v);
            }
        }

        // Condition not met anywhere in the range
        return {-1, -1}; 
    }
};
