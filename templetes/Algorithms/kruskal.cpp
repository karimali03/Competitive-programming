#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
using namespace std;

struct dsu {
	vector<int> rank, parent;
	int forests;

	dsu(int n) : forests(n) {
		rank = vector<int>(n), parent = vector<int>(n);

		for (int i = 0; i < n; ++i)
			parent[i] = i, rank[i] = 1;
	}

	void link(int x, int y) {
		if (rank[x] > rank[y])
			swap(x, y);	// force x to be smaller

		parent[x] = y;
		if (rank[x] == rank[y])	// equal case
			rank[y]++;
	}


	int find_set(int x) {
		if (x == parent[x])
			return x;
		// This is the path compression
		// the top parent is returned and we re-link
		return parent[x] = find_set(parent[x]);
	}

	bool union_sets(int x, int y) {
		x = find_set(x), y = find_set(y);
		if (x != y) {	// Different components
			link(x, y);
			forests--;	// 2 merged into 1
		}
		return x != y;
	}
};

struct edge {
	int from, to, w;

	edge(int from, int to, int w) :
			from(from), to(to), w(w) {
	}

	bool operator <(const edge &e) const {
		return w < e.w;
	}
};

int MST_Kruskal(vector<edge> &edgeList, int n) { // O(E logV)
	dsu uf(n);
	vector<edge> edges;			 // Save MST edges
	int mstCost = 0;

	sort(edgeList.begin(), edgeList.end());

	for(auto& e : edgeList) {
		if (uf.union_sets(e.from, e.to)) {
			// If added, then part of tree
			mstCost += e.w;
			edges.push_back(e);
		}
	}
	// if size of edges != n-1, then no full MST
	return mstCost;
}



int main() {
	return 0;
}
