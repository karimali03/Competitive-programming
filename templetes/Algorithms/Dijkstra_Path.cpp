#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
using namespace std;

const int OO = (int) 1e6;

struct edge {
	int to, w, from;

	edge(int from = 0 ,int to = 0, int w = 0) :
			from(from) , to(to), w(w) {
	}

	bool operator <(const edge &e) const {
		return w > e.w;
	}
};



// O(E logV)
vector<int>prv;

vector<int> Dijkstra(const vector<vector<edge>> &adjList, int n, int src) {
	vector<int> dist(n, OO);
    prv = vector<int>(n,-1);
	priority_queue<edge> q;	
	q.push(edge{ -1 , src , 0});

	while (!q.empty()) {
		edge mn = q.top();
		int idx = mn.to;
		q.pop();
		if(dist[idx] != OO) continue;
		dist[idx] = mn.w;
        prv[idx] = mn.from;

		for (const auto &edge : adjList[idx]) {
			int to = edge.to, weight = edge.w;
			if (dist[to] == OO) {
				q.push( {idx , to, dist[idx] + weight });
			}

		}
	}

	return dist;
}

vector<int> buildPath(int end){
    vector<int> ret;
    for(int i = end ; i != -1 && ret.size() < prv.size() ; i = prv[i]){
        ret.push_back(i);
    }
    reverse(ret.begin(),ret.end());
    return ret;
}


int main(){
    freopen("in.txt", "rt", stdin);

	vector<vector<edge> > adjList;
	int n, m;	
	cin >> n >> m;

	adjList = vector<vector<edge> >(n);

	for (int i = 0; i < m; ++i) {
		int from, to, weight;
		cin >> from >> to >> weight;
		adjList[from].push_back( { from, to, weight });
	}

	
	vector<int> sp = Dijkstra(adjList, n, 0);

	

	int target = 1;
	vector<int> path = buildPath(target);
   
	for (int x : path)
		cout << x << " ";	// 0 2 4 1
        cout<<"\n";
	return 0;
}



/*
5 7
0 2 4
0 3 10
2 3 2
2 4 3
3 4 2
4 1 2
1 2 2
*/