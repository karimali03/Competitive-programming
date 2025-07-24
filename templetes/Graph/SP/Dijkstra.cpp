 
const int OO =  1e9;
 
struct edge {
	int to, w;
 
	edge(int to = 0, int w = 0) :
			to(to), w(w) {
	}
 
	bool operator <(const edge &e) const {
		return w > e.w;
	}
};
 
 
 
// O(E logV)
vector<int> Dijkstra(const vector<vector<edge>> &adjList, int n, int src) {
	vector<int> dist(n, OO);
	priority_queue<edge> q;	
	q.push(edge(src, 0));
 
	while (!q.empty()) {
		edge mn = q.top();
		int idx = mn.to;
		q.pop();
		if(dist[idx] != OO) continue;
		dist[idx] = mn.w;
 
 
		for (const auto &edge : adjList[idx]) {
			int to = edge.to, weight = edge.w;
			if (dist[to] == OO) {
				q.push( {to, dist[idx] + weight });
			}
 
		}
	}
 
	return dist;
}
