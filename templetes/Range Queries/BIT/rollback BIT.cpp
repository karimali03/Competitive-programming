struct RollbackBIT {
    int n;
    vector<int> tree;
    vector<pair<int, int>> history; // Stores {index, value_added}

    RollbackBIT(int sz) : n(sz), tree(sz + 1, 0) {}

    // Add val to index idx
    void add(int idx, int val) {
        history.push_back({idx, val}); // Record for rollback
        for (; idx <= n; idx += idx & -idx) 
            tree[idx] += val;
    }

    // Prefix sum up to idx
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) 
            sum += tree[idx];
        return sum;
    }

    // Get range sum [l, r]
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }

    // --- Rollback Features ---

    // Get current state ID
    int snapshot() {
        return history.size();
    }

    // Revert to a previous state ID
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto [idx, val] = history.back();
            history.pop_back();
            // Manually subtract to undo (don't call add() here)
            for (; idx <= n; idx += idx & -idx) 
                tree[idx] -= val;
        }
    }
};
