#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

struct Edge {
    int to;
    ll w;
};

const ll INF = (1LL << 62);

struct SegTreeGraph {
    int n;
    int nodes;

    vector<int> in, out;

    /*
        opposite[i] is the Euler position of the other
        house with the same color.
    */
    vector<int> opposite;

    vector<vector<Edge>> g;

    SegTreeGraph(int n, const vector<int>& opposite)
        : n(n), opposite(opposite) {

        nodes = n;

        int max_nodes = 3 * n + 5;

        in.resize(4 * n + 5);
        out.resize(4 * n + 5);
        g.resize(max_nodes);

        build(1, 1, n);
    }

    void add(int from, int to, ll w = 0) {
        g[from].push_back({to, w});
    }

    void build(int p, int l, int r) {
        if (l == r) {
            /*
                For RangeToNode:

                    x -> segment node

                so the in-leaf is x.
            */
            in[p] = l;

            /*
                For NodeToRange:

                    segment node -> not x

                so the out-leaf is opposite[x].
            */
            out[p] = opposite[l];

            return;
        }

        int mid = (l + r) >> 1;

        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);

        in[p] = ++nodes;
        out[p] = ++nodes;

        // out parent -> children
        add(out[p], out[p * 2], 0);
        add(out[p], out[p * 2 + 1], 0);

        // in parent <- children
        add(in[p * 2], in[p], 0);
        add(in[p * 2 + 1], in[p], 0);
    }

    void NodeToRange(
        int u,
        int ql,
        int qr,
        ll w,
        int p,
        int l,
        int r
    ) {
        if (ql <= l && r <= qr) {
            add(u, out[p], w);
            return;
        }

        int mid = (l + r) >> 1;

        if (ql <= mid) {
            NodeToRange(
                u, ql, qr, w,
                p * 2, l, mid
            );
        }

        if (qr > mid) {
            NodeToRange(
                u, ql, qr, w,
                p * 2 + 1, mid + 1, r
            );
        }
    }

    void NodeToRange(int u, int ql, int qr, ll w = 0) {
        if (ql > qr) return;

        NodeToRange(
            u, ql, qr, w,
            1, 1, n
        );
    }

    void RangeToNode(
        int u,
        int ql,
        int qr,
        ll w,
        int p,
        int l,
        int r
    ) {
        if (ql <= l && r <= qr) {
            add(in[p], u, w);
            return;
        }

        int mid = (l + r) >> 1;

        if (ql <= mid) {
            RangeToNode(
                u, ql, qr, w,
                p * 2, l, mid
            );
        }

        if (qr > mid) {
            RangeToNode(
                u, ql, qr, w,
                p * 2 + 1, mid + 1, r
            );
        }
    }

    void RangeToNode(int u, int ql, int qr, ll w = 0) {
        if (ql > qr) return;

        RangeToNode(
            u, ql, qr, w,
            1, 1, n
        );
    }

    void RangeToRange(
        int l1,
        int r1,
        int l2,
        int r2,
        ll w
    ) {
        int aux = ++nodes;

        RangeToNode(aux, l1, r1, w);
        NodeToRange(aux, l2, r2, 0);
    }

    /*
        u and every x in [l,r] cannot both be selected.

        Clause:

            not u OR not x

        Implications:

            u -> not x
            x -> not u
    */
    void addConflictRange(int u, int l, int r) {
        if (l > r) return;

        // u -> opposite[x]
        NodeToRange(u, l, r, 0);

        // x -> opposite[u]
        RangeToNode(opposite[u], l, r, 0);
    }
};

struct TwoSat {
    int n;
    int vertices;

    int timer;
    int scc_count;

    vector<vector<Edge>>& adj;

    vector<int> tin;
    vector<int> low;
    vector<int> comp;
    vector<int> st;

    vector<bool> in_stack;
    vector<bool> assignment;

    /*
        first[i] and second[i] are the two literals
        representing color i.
    */
    vector<int> first;
    vector<int> second;

    TwoSat(
        int variables,
        int vertices,
        vector<vector<Edge>>& graph,
        const vector<int>& first,
        const vector<int>& second
    ) : adj(graph), first(first), second(second) {

        n = variables;
        this->vertices = vertices;

        tin.resize(vertices + 1);
        low.resize(vertices + 1);
        comp.resize(vertices + 1);

        in_stack.resize(vertices + 1);
        assignment.resize(n + 1);
    }

    /*
        Iterative Tarjan.

        We avoid recursive DFS because the compressed
        implication graph can contain around 6 * n nodes.
    */
    void dfs(int start) {
        vector<int> dfs_stack;
        vector<int> parent(vertices + 1, 0);
        vector<int> edge_index(vertices + 1, 0);

        tin[start] = low[start] = timer++;

        st.push_back(start);
        dfs_stack.push_back(start);

        in_stack[start] = true;

        while (!dfs_stack.empty()) {
            int v = dfs_stack.back();

            if (edge_index[v] < (int)adj[v].size()) {
                int u = adj[v][edge_index[v]++].to;

                if (tin[u] == -1) {
                    parent[u] = v;

                    tin[u] = low[u] = timer++;

                    st.push_back(u);
                    dfs_stack.push_back(u);

                    in_stack[u] = true;
                }
                else if (in_stack[u]) {
                    low[v] = min(low[v], tin[u]);
                }
            }
            else {
                dfs_stack.pop_back();

                if (parent[v] != 0) {
                    low[parent[v]] = min(
                        low[parent[v]],
                        low[v]
                    );
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
        }
    }

    bool solve() {
        timer = 0;
        scc_count = 0;

        st.clear();

        fill(all(tin), -1);
        fill(all(low), 0);
        fill(all(comp), -1);
        fill(all(in_stack), false);

        // Find all SCCs using Tarjan.
        for (int v = 1; v <= vertices; v++) {
            if (tin[v] == -1) {
                dfs(v);
            }
        }

        // Check contradictions and construct an assignment.
        for (int i = 1; i <= n; i++) {
            int x = first[i];
            int not_x = second[i];

            if (comp[x] == comp[not_x]) {
                return false;
            }

            /*
                Tarjan numbers sink SCCs first,
                so the comparison is <.
            */
            assignment[i] = comp[x] < comp[not_x];
        }

        return true;
    }
};

void solve(int test_case) {
    int n;
    cin >> n;

    int vertices = 2 * n;

    vi color(vertices + 1);

    /*
        houses[color] contains the two original
        vertices with this color.
    */
    vector<array<int, 2>> houses(n + 1);
    vi color_count(n + 1, 0);

    for (int i = 1; i <= vertices; i++) {
        cin >> color[i];

        houses[color[i]][color_count[color[i]]++] = i;
    }

    /*
        other[u] is the other original tree vertex
        with the same color as u.
    */
    vi other(vertices + 1);

    for (int c = 1; c <= n; c++) {
        int u = houses[c][0];
        int v = houses[c][1];

        other[u] = v;
        other[v] = u;
    }

    vii tree(vertices + 1);

    for (int i = 1; i < vertices; i++) {
        int u, v;
        cin >> u >> v;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    /*
        Root the tree at vertex 1 and build its Euler tour.

        Every subtree becomes an interval:

            subtree(v) = [tin[v], tout[v]]
    */
    vi tin(vertices + 1);
    vi tout(vertices + 1);
    vi euler(vertices + 1);

    vi parent(vertices + 1);
    vi depth(vertices + 1);
    vi edge_index(vertices + 1, 0);

    vi st;

    int timer = 0;

    parent[1] = 1;
    st.push_back(1);

    while (!st.empty()) {
        int v = st.back();

        if (edge_index[v] == 0) {
            tin[v] = ++timer;
            euler[timer] = v;
        }

        if (edge_index[v] < (int)tree[v].size()) {
            int u = tree[v][edge_index[v]++];

            if (u == parent[v]) continue;

            parent[u] = v;
            depth[u] = depth[v] + 1;

            st.push_back(u);
        }
        else {
            tout[v] = timer;
            st.pop_back();
        }
    }

    int LOG = 1;

    while ((1LL << LOG) <= vertices) {
        LOG++;
    }

    vii up(LOG, vi(vertices + 1));

    for (int v = 1; v <= vertices; v++) {
        up[0][v] = parent[v];
    }

    for (int bit = 1; bit < LOG; bit++) {
        for (int v = 1; v <= vertices; v++) {
            up[bit][v] =
                up[bit - 1][up[bit - 1][v]];
        }
    }

    auto is_ancestor = [&](int u, int v) {
        return tin[u] <= tin[v] &&
               tout[v] <= tout[u];
    };

    auto jump = [&](int v, int distance) {
        for (int bit = 0; bit < LOG; bit++) {
            if ((distance >> bit) & 1LL) {
                v = up[bit][v];
            }
        }

        return v;
    };

    /*
        opposite_position[p] is the Euler position
        of the other house having the same color.

        We use Euler positions as the literal IDs.
    */
    vi opposite_position(vertices + 1);

    for (int p = 1; p <= vertices; p++) {
        int original_vertex = euler[p];

        opposite_position[p] =
            tin[other[original_vertex]];
    }

    SegTreeGraph sg(
        vertices,
        opposite_position
    );

    for (int u = 1; u <= vertices; u++) {
        int v = other[u];

        int literal_u = tin[u];

        if (!is_ancestor(v, u)) {
            /*
                u is outside subtree(v).

                The path from u to x contains v
                exactly when x belongs to subtree(v).
            */
            sg.addConflictRange(
                literal_u,
                tin[v],
                tout[v]
            );
        }
        else {
            /*
                v is an ancestor of u.

                Find the child of v which is also
                an ancestor of u.
            */
            int distance =
                depth[u] - depth[v] - 1;

            int child = jump(u, distance);

            /*
                The path from u to x contains v
                exactly when x is outside subtree(child).
            */
            sg.addConflictRange(
                literal_u,
                1,
                tin[child] - 1
            );

            sg.addConflictRange(
                literal_u,
                tout[child] + 1,
                vertices
            );
        }
    }

    /*
        For every color, store the Euler positions
        of its two houses.
    */
    vi first(n + 1);
    vi second(n + 1);

    for (int c = 1; c <= n; c++) {
        first[c] = tin[houses[c][0]];
        second[c] = tin[houses[c][1]];
    }

    TwoSat two_sat(
        n,
        sg.nodes,
        sg.g,
        first,
        second
    );

    if (!two_sat.solve()) {
        NA;
        return;
    }

    vi answer;

    for (int c = 1; c <= n; c++) {
        if (two_sat.assignment[c]) {
            answer.push_back(houses[c][0]);
        }
        else {
            answer.push_back(houses[c][1]);
        }
    }

    cout << answer << ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}