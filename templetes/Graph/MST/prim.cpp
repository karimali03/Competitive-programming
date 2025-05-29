const int OO = 2 * 1e6 * 1000;	


struct edge {
	int to, w;

	edge(int to, int w) :
			to(to), w(w) {
	}

	bool operator <(const edge &e) const {
		return w > e.w;
	}
};

// O(E logV)
int MST(const vector<vector<edge>> &adjList, int n, int src=0) {
	vector<int> dist(n, OO);
	vector<bool> vis(n, 0);
	dist[src] = 0;
	int mstCost = 0;

	priority_queue<edge> q;	// small to large
	q.push(edge(src, 0));

	while (!q.empty()) {
		// Get node with the minimum distance
		edge mnEdge = q.top();
		int mnIdx = mnEdge.to;
		q.pop();

		if (vis[mnIdx])	// visited
			continue;

		mstCost += mnEdge.w;

		for (const auto &edge : adjList[mnIdx]) {	// relax
			int to = edge.to, weight = edge.w;

			if (dist[to] > weight) {
				dist[to] = weight;
				q.push( {to, dist[to] });
			}
		}
		vis[mnIdx] = true;
	}
	return mstCost;
}
