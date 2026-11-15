#include <bits/stdc++.h>
using namespace std;

// Generic, unweighted matroid intersection.
//
// Each matroid must implement:
//   build(in)          : prepare for the currently chosen set in[e] == true
//   canAdd(x)          : is I + x independent?
//   canSwap(y, x)      : is I - y + x independent?
// Here y is selected, x is unselected, and both matroids use the SAME
// ground set {0, 1, ..., m-1}.
//
// With O(1) oracles, complexity is O(r^2 * m) for max answer size r.
template<class M1, class M2>
struct MatroidIntersection {
    int m;
    M1 a;
    M2 b;

    MatroidIntersection(int m, M1 a, M2 b)
        : m(m), a(move(a)), b(move(b)) {}

    vector<int> solve() {
        vector<char> in(m, false);

        while (true) {
            a.build(in);
            b.build(in);

            vector<int> inside, outside;
            for (int e = 0; e < m; ++e) {
                (in[e] ? inside : outside).push_back(e);
            }

            vector<int> prv(m, -1);
            queue<int> q;

            // Sources: elements that can be added to M1 directly.
            for (int x : outside) {
                if (a.canAdd(x)) {
                    prv[x] = -2;
                    q.push(x);
                }
            }

            int sink = -1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();

                if (!in[x]) {
                    // Sinks: elements that can be added to M2 directly.
                    if (b.canAdd(x)) {
                        sink = x;
                        break;
                    }

                    // Outside -> inside: exchange in M2.
                    for (int y : inside) {
                        if (prv[y] == -1 && b.canSwap(y, x)) {
                            prv[y] = x;
                            q.push(y);
                        }
                    }
                } else {
                    // Inside -> outside: exchange in M1.
                    for (int y : outside) {
                        if (prv[y] == -1 && a.canSwap(x, y)) {
                            prv[y] = x;
                            q.push(y);
                        }
                    }
                }
            }

            if (sink == -1) break; // Maximum common independent set.

            // Shortest augmenting path: flip membership (+1 net element).
            for (int x = sink; x != -2; x = prv[x]) in[x] ^= 1;
        }

        vector<int> answer;
        for (int e = 0; e < m; ++e) {
            if (in[e]) answer.push_back(e);
        }
        return answer;
    }
};

// EXAMPLE ORACLE 1: graphic matroid (selected edges must form a forest).
struct GraphicMatroid {
    struct DSU {
        vector<int> p;
        DSU(int n) : p(n, -1) {}
        int find(int u) { return p[u] < 0 ? u : p[u] = find(p[u]); }
        void unite(int u, int v) {
            u = find(u), v = find(v);
            if (u == v) return;
            if (p[u] > p[v]) swap(u, v);
            p[u] += p[v];
            p[v] = u;
        }
    };

    int n;
    vector<pair<int, int>> edge; // 0-based endpoints
    vector<int> comp, tin, tout, child;

    GraphicMatroid(int n, vector<pair<int, int>> edge)
        : n(n), edge(move(edge)) {}

    void build(const vector<char>& in) {
        int m = (int)edge.size();
        DSU dsu(n);
        vector<vector<pair<int, int>>> tree(n);

        for (int e = 0; e < m; ++e) {
            if (!in[e]) continue;
            auto [u, v] = edge[e];
            dsu.unite(u, v);
            tree[u].push_back({v, e});
            tree[v].push_back({u, e});
        }

        comp.resize(n);
        for (int u = 0; u < n; ++u) comp[u] = dsu.find(u);

        // Euler tour: selected edge e belongs to path u-v iff
        // exactly one endpoint is in the subtree of child[e].
        tin.assign(n, -1);
        tout.resize(n);
        child.assign(m, -1);
        int timer = 0;

        auto dfs = [&](auto&& self, int u, int parent) -> void {
            tin[u] = timer++;
            for (auto [v, e] : tree[u]) {
                if (v == parent) continue;
                child[e] = v;
                self(self, v, u);
            }
            tout[u] = timer++;
        };

        for (int u = 0; u < n; ++u) {
            if (tin[u] == -1) dfs(dfs, u, -1);
        }
    }

    bool canAdd(int x) const {
        auto [u, v] = edge[x];
        return comp[u] != comp[v];
    }

    bool inSubtree(int u, int root) const {
        return tin[root] <= tin[u] && tout[u] <= tout[root];
    }

    bool canSwap(int y, int x) const {
        if (canAdd(x)) return true;
        auto [u, v] = edge[x];
        int root = child[y]; // y is selected.
        return inSubtree(u, root) != inSubtree(v, root);
    }
};

// EXAMPLE ORACLE 2: partition matroid (at most one element per group).
struct PartitionMatroid {
    int groups;
    vector<int> group; // group[e] in [0, groups)
    vector<int> owner;

    PartitionMatroid(int groups, vector<int> group)
        : groups(groups), group(move(group)) {}

    void build(const vector<char>& in) {
        owner.assign(groups, -1);
        for (int e = 0; e < (int)group.size(); ++e) {
            if (in[e]) owner[group[e]] = e;
        }
    }

    bool canAdd(int x) const {
        return owner[group[x]] == -1;
    }

    bool canSwap(int y, int x) const {
        return canAdd(x) || owner[group[x]] == y;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> endpoints(m);
    vector<int> colors(m);

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        endpoints[i] = {u - 1, v - 1};
        colors[i] = c - 1;
    }

    MatroidIntersection mi(
        m,
        GraphicMatroid(n, endpoints),
        PartitionMatroid(n - 1, colors)
    );

    vector<int> answer = mi.solve();
    if ((int)answer.size() != n - 1) {
        cout << -1 << '\n';
        return 0;
    }

    for (int e : answer) cout << e + 1 << ' ';
    cout << '\n';
}