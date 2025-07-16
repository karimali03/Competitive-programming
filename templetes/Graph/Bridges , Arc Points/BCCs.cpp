/*
============================ BLOCK-CUT TREE TEMPLATE ============================

USAGE:
- Use for undirected graphs to find:
    - Biconnected components (BCCs)
    - Articulation points (cutpoints)
    - Block-Cut Tree (BCT) for path queries, LCA, etc.

INPUT:
- Graph `g` as adjacency list
- 0-based node indices

OUTPUT:
- is_cutpoint[u] → true if `u` is a cutpoint
- id[u] → maps original node `u` to a node in the block-cut tree
- blockcut_tree → tree of cutpoints and BCCs (size ≤ 2 * n)

NOTES:
- Each node in blockcut_tree is either:
    - A cutpoint (if u is articulation point, id[u] points to a unique node)
    - A BCC node (if u is non-articulation, id[u] points to its BCC node)
- Use `id[a]`, `id[b]`, etc. for LCA or path queries in blockcut_tree

=================================================================================
*/
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

