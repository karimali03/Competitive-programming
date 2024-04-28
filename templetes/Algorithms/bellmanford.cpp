#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
using namespace std;


const int OO = (int) 1e6;


struct edge {
	int from, to, w;

	edge(int from, int to, int w) :
			from(from), to(to), w(w) {
	}
};

vector<int> BellmanFord(vector<edge> &edgeList, int n, int src) {
	vector<int> dist(n, OO);
	dist[src] = 0;

	for (int it = 0; it < n - 1; ++it) {
		bool any_updates = false;
		// 2 inner loops just iterate on edges relax all to nodes
		for (int j = 0; j < (int) edgeList.size(); ++j) {
			edge &ne = edgeList[j];	// enhance its ne.to

			if (dist[ne.to] > dist[ne.from] + ne.w) {
				dist[ne.to] = dist[ne.from] + ne.w;
				any_updates = true;
			}
		}
		if (!any_updates) {
			break;
            // if a complete iteration does nothing, then more iterations doesn't help
		}
	}
	return dist;
}


int main() {
	vector<edge> edgeList { { 0, 1, 1 }, { 1, 2, 99 }, { 2, 3, 5 }, { 1, 4, 1 }, { 4, 2, 3 }, { 4, 5, 6 }, { 5, 3, 7 } };

	vector<int> sp = BellmanFord(edgeList, 6, 0);

	for (int i = 0; i < (int) sp.size(); ++i)
		cout << i << " " << sp[i] << "\n";


	return 0;
}
