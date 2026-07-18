struct DSU {
    int n;
    vector<int> parent, rank;
    vector<int> len;  // len[v] = distance/length from v to its parent

    DSU(int _n) : n(_n) {
        parent.resize(n + 1);
        rank.assign(n + 1, 0);
        len.assign(n + 1, 0);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    // Find with path compression that updates len[v] to root distance
    int find(int v) {
        if (v == parent[v]) return v;
        int p = parent[v];
        parent[v] = find(p);
        len[v] += len[p];  // accumulate distance up the tree
        return parent[v];
    }

    // Union two sets and assign len for the merged edge (weight = 1 here)
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        len[b] = 1;  // distance from b to its new parent a is 1
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

