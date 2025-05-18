struct DSU {
    vector<int> parent, size, parity;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        parity.assign(n + 1, 0);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int get(int x) {
        if (x == parent[x]) return x;
        int root = get(parent[x]);
        if(root != parent[x])
        parity[x] = (parity[x] + parity[parent[x]]) ;
        parent[x] = root;
        return root;
    }

    bool merge(int x, int y) {
        int rx = get(x), ry = get(y);
        if (rx == ry) {
            // Check if they are in the same set with the same parity (i.e., odd cycle)
            return (parity[x] + parity[y]) % 2 == 1;
        }
        // Merge x's root into y's root, update parity
        parent[rx] = ry;
        parity[rx] = (1 + parity[x] + parity[y]);
        return true;
    }
};
