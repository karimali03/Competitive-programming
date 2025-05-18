struct dsu {
    vector<int> size, par;
    int cc;

    dsu(int n) : cc(n), size(n + 1, 1), par(n + 1) {
        for (int i = 0; i <= n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

};


struct edge {
	int from, to, w;

	edge(int from = -1 , int to = -1, int w = -1) :
			from(from), to(to), w(w) {
	}

	bool operator <(const edge &e) const {
		return w < e.w;
	}
};

int MST_Kruskal(vector<edge> &edgeList, int n) { // O(E logV)
	dsu uf(n);
	vector<edge> edges;	
	int mstCost = 0;

	sort(edgeList.begin(), edgeList.end());

	for(auto& e : edgeList) {
		if (uf.merge(e.from, e.to)) {
			// If added, then part of tree
			mstCost += e.w;
			edges.push_back(e);
		}
	}
	// if size of edges != n-1, then no full MST
	return mstCost;
}
