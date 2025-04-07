vector<int> topsort(vii &adjList) {	// O( E+V )
	int sz = adjList.size();
	vector<int> indegree(sz, 0);	// compute indegrees of nodes
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;
    int time = 0 ;
	queue<int>ready;	// add all current nodes that has indegree(0)
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push({d[i] ,i});
    
	vector<int> ordering;
	while (!ready.empty()) {	
		auto i = ready.top();
		ready.pop();
		ordering.push_back(i[1]);
		for (int j : adjList[i[1]])	// remove its outgoing edges
			if (--indegree[j] == 0)	// If a neighbor is ready, add it
				ready.push({ d[j] ,j});
	}
	if (ordering.size() != adjList.size())
		ordering.clear();				//There are cycles
	return ordering;
}
