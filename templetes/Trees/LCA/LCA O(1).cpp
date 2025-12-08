struct LCA {
    int n;
    int tour_idx;
    vector<vector<int>> adj;
    vector<int> first_occurrence; // Index of node in Euler tour
    vector<int> euler_tour;       // Nodes in tour
    vector<int> depth_arr;        // Depths corresponding to euler_tour
    vector<vector<int>> st;       // Sparse Table
    vector<int> logs;             // Precomputed logarithms

    LCA(int _n) : n(_n), tour_idx(0) {
        adj.resize(n);
        first_occurrence.resize(n);
        // Euler tour size is roughly 2*N
        euler_tour.reserve(2 * n);
        depth_arr.reserve(2 * n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u, int d) {
        first_occurrence[u] = euler_tour.size();
        euler_tour.push_back(u);
        depth_arr.push_back(d);

        for (int v : adj[u]) {
            dfs(v, d + 1);
            euler_tour.push_back(u);
            depth_arr.push_back(d);
        }
    }

    void build() {
        dfs(0, 0); // Start DFS from root 0

        int m = euler_tour.size();
        logs.resize(m + 1);
        logs[1] = 0;
        for (int i = 2; i <= m; i++)
            logs[i] = logs[i / 2] + 1;

        int K = logs[m];
        st.assign(m, vector<int>(K + 1));

        // Base case: intervals of length 1
        for (int i = 0; i < m; i++)
            st[i][0] = i;

        // Build Sparse Table
        for (int j = 1; j <= K; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                int l_idx = st[i][j - 1];
                int r_idx = st[i + (1 << (j - 1))][j - 1];
                // Compare depths
                if (depth_arr[l_idx] < depth_arr[r_idx])
                    st[i][j] = l_idx;
                else
                    st[i][j] = r_idx;
            }
        }
    }

    int query(int u, int v) {
        int L = first_occurrence[u];
        int R = first_occurrence[v];
        if (L > R) swap(L, R);

        int j = logs[R - L + 1];
        int l_idx = st[L][j];
        int r_idx = st[R - (1 << j) + 1][j];

        if (depth_arr[l_idx] < depth_arr[r_idx])
            return euler_tour[l_idx];
        else
            return euler_tour[r_idx];
    }
};
