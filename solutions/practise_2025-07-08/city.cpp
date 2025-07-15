#include <bits/stdc++.h>
using namespace std;

// === Biconnected Components + Block-Cut Tree ===
vector<vector<int>> biconnected_components(vector<vector<int>> &g,
                                           vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();

	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n), low(n);
	is_cutpoint.assign(n, false);

	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : g[node]) {
			if (son == parent) continue;
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};

	int timer = 0;
	dfs(0, -1, timer);
	id.resize(n);

	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);  // dummy
		int node_id = 1;

		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}

		for (auto &comp : comps) {
			int new_node = node_id++;
			t.push_back({});
			for (int u : comp) {
				if (!is_cutpoint[u]) {
					id[u] = new_node;
				} else {
					t[new_node].push_back(id[u]);
					t[id[u]].push_back(new_node);
				}
			}
		}
		t.erase(t.begin());  // remove dummy
		for (int i = 0; i < (int)t.size(); ++i) {
			for (int &x : t[i]) if (x > 0) x--;
		}
		for (int &x : id) if (x > 0) x--;
		return t;
	};

	return build_tree();
}

// === LCA Template ===
const int N = 200005;
const int LOG = 18;
vector<int> adj[N];
int up[N][LOG],lvl[N];

void init(int n) {
	for (int i = 0; i < n; ++i) {
		adj[i].clear();
		lvl[i] = 0;
		for (int j = 0; j < LOG; ++j) {
			up[i][j] = 0;
		}
	}
}

int merge(int a, int b) {
	return a + b;
}

void dfs(int v, int p) {
	for (auto to : adj[v]) {
		if (to == p) continue;
		lvl[to] = lvl[v] + 1;
		up[to][0] = v;
		for (int j = 1; j < LOG; j++) {
			up[to][j] = up[up[to][j - 1]][j - 1];
		}
		dfs(to, v);
	}
}

void build(int root = 0) {
	lvl[root] = 0;
	up[root][0] = root;
	for (int j = 1; j < LOG; ++j) {
		up[root][j] = root;
	}
	dfs(root, -1);
}

int lca(int u, int v) {
	if (lvl[u] < lvl[v]) swap(u, v);
	int diff = lvl[u] - lvl[v];
	for (int j = LOG - 1; j >= 0; --j)
		if ((diff >> j) & 1) u = up[u][j];
	if (u == v) return u;
	for (int j = LOG - 1; j >= 0; --j)
		if (up[u][j] != up[v][j]) {
			u = up[u][j];
			v = up[v][j];
		}
	return up[u][0];
}

// === Main ===
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	vector<int> id;
	vector<bool> is_cutpoint;
	vector<vector<int>> blockcut_tree = biconnected_components(g, is_cutpoint, id);

	int bct_size = blockcut_tree.size();
	init(bct_size);

	// Build LCA tree on block-cut tree
	for (int u = 0; u < bct_size; ++u) {
		for (int v : blockcut_tree[u]) {
			adj[u].push_back(v);
		}
	}
	build(0);

	// Check if node z is on path from x to y
	auto on_path = [&](int x, int y, int z) {
		int l = lca(x, y);
		int l1 = lca(x, z);
		int l2 = lca(y, z);
		return z == l || (l1 == z && l2 == l) || (l2 == z && l1 == l);
	};

	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--, c--;

		if (a == c || b == c) {
			cout << "NO\n";
			continue;
		}
		if (!is_cutpoint[c]) {
			cout << "YES\n";
			continue;
		}
		if (on_path(id[a], id[b], id[c])) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
}
