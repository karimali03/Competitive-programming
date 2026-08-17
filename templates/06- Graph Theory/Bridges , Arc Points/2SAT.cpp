struct TwoSat {
    int n;
    int timer;
    int scc_count;

    vector<vector<int>> adj;

    vector<int> tin;
    vector<int> low;
    vector<int> comp;
    vector<int> st;

    vector<bool> in_stack;
    vector<bool> assignment;

    TwoSat(int variables) {
        n = variables;

        int vertices = 2 * n;

        adj.resize(vertices);
        tin.resize(vertices);
        low.resize(vertices);
        comp.resize(vertices);
        in_stack.resize(vertices);
        assignment.resize(n);
    }

    // Returns the vertex representing:
    // x_var       when negated = false
    // not x_var   when negated = true
    int get_literal(int var, bool negated) {
        return 2 * var + negated;
    }

    void add_clause(int a, bool neg_a, int b, bool neg_b) {
        int x = get_literal(a, neg_a);
        int y = get_literal(b, neg_b);

        int not_x = x ^ 1;
        int not_y = y ^ 1;

        // (x OR y) becomes:
        // not x -> y
        // not y -> x
        adj[not_x].push_back(y);
        adj[not_y].push_back(x);
    }

    // (A OR B)
    void OR(int a, bool neg_a, int b, bool neg_b) {
        add_clause(a, neg_a, b, neg_b);
    }

    // A must be true
    // A = (A OR A)
    void MUST(int a, bool neg_a) {
        add_clause(a, neg_a, a, neg_a);
    }

    // A -> B
    // equivalent to (!A OR B)
    void IMPLIES(int a, bool neg_a, int b, bool neg_b) {
        add_clause(a, !neg_a, b, neg_b);
    }

    // A and B cannot both be true
    // !(A AND B) = (!A OR !B)
    void MUTEX(int a, bool neg_a, int b, bool neg_b) {
        add_clause(a, !neg_a, b, !neg_b);
    }

    // exactly one of A,B is true
    // (A OR B) AND (!A OR !B)
    void XOR(int a, bool neg_a, int b, bool neg_b) {
        add_clause(a, neg_a, b, neg_b);
        add_clause(a, !neg_a, b, !neg_b);
    }

    // A == B
    // (!A OR B) AND (A OR !B)
    void XNOR(int a, bool neg_a, int b, bool neg_b) {
        add_clause(a, !neg_a, b, neg_b);
        add_clause(a, neg_a, b, !neg_b);
    }



    // add auxiliary variable
    int addVar() {
        int id = n++;

        adj.resize(2 * n);
        tin.resize(2 * n);
        low.resize(2 * n);
        comp.resize(2 * n);
        in_stack.resize(2 * n);
        assignment.resize(n);

        return id;
    }

    // At most one literal TRUE - O(k)
    void AT_MOST_ONE_TRUE(vector<pair<int,bool>> &v) {
        int k = v.size();
        if (k <= 1) return;

        // s = "one of previous literals is true"
        int s = addVar();

        // x0 -> s
        // !x0 OR s
        add_clause(v[0].first, !v[0].second, s, false);

        for (int i = 1; i < k - 1; i++) {
            int ns = addVar();

            // xi -> ns
            add_clause(v[i].first, !v[i].second, ns, false);

            // s -> ns
            add_clause(s, true, ns, false);

            // cannot have xi=true AND previous=true
            // !xi OR !s
            add_clause(v[i].first, !v[i].second, s, true);

            s = ns;
        }

        // last cannot be true if something before was true
        add_clause(v.back().first, !v.back().second, s, true);
    }

    // At most one literal FALSE - O(k)
    void AT_MOST_ONE_FALSE(vector<pair<int,bool>> v) {
        for (auto &[x, neg] : v)
            neg ^= 1;

        AT_MOST_ONE_TRUE(v);
    }

    void dfs(int v) {
        tin[v] = low[v] = timer++;

        st.push_back(v);
        in_stack[v] = true;

        for (int u : adj[v]) {
            if (tin[u] == -1) {
                dfs(u);
                low[v] = min(low[v], low[u]);
            }
            else if (in_stack[u]) {
                low[v] = min(low[v], tin[u]);
            }
        }

        if (low[v] == tin[v]) {
            while (true) {
                int u = st.back();
                st.pop_back();

                in_stack[u] = false;
                comp[u] = scc_count;

                if (u == v)
                    break;
            }

            scc_count++;
        }
    }

    bool solve() {
        int vertices = 2 * n;

        timer = 0;
        scc_count = 0;
        st.clear();

        fill(tin.begin(), tin.end(), -1);
        fill(low.begin(), low.end(), 0);
        fill(comp.begin(), comp.end(), -1);
        fill(in_stack.begin(), in_stack.end(), false);

        // Find all SCCs using Tarjan.
        for (int v = 0; v < vertices; v++) {
            if (tin[v] == -1)
                dfs(v);
        }

        // Check contradictions and construct an assignment.
        for (int i = 0; i < n; i++) {
            int x = 2 * i;
            int not_x = x ^ 1;

            if (comp[x] == comp[not_x])
                return false;

            // Standard Tarjan numbers sink SCCs first,
            // so the comparison is <.
            assignment[i] = comp[x] < comp[not_x];
        }

        return true;
    }
};
