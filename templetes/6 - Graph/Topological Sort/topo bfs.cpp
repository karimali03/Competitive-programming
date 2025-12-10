/*Topological Sort - Key Notes
 1. Use when there are "do X before Y" constraints (DAG only).
 2. Good for task scheduling, build systems, course planning.
 3. Node is processed after all its prerequisites are done.
   => Useful to aggregate info from dependencies (e.g., DP on DAG).
 4. Detects cycles: if topo sort not possible, graph has a cycle.
 5. In Khan’s algorithm, replacing the queue with a priority queue can list the
    lexicographical ordering
 6. We can also list ALL the possible orderings using the backtracking
    technique
 7. shortest path -> bfs , longest path -> topo sort !
*/
vector<int> topo_sort(vector<vector<int>> &adj) {	// O( E+V )
            int sz = adj.size();
            vector<int> indegree(sz, 0);	
            for (int i = 0; i < sz; ++i)
                for (int j : adj[i])
                    indegree[j]++;
        
            queue<int>ready;	
            for (int i = 0; i < sz; ++i)  
            if (!indegree[i])    ready.push(i);
            
            vector<int> ordering;
            while (!ready.empty()) {	
                auto cur = ready.front();
                ready.pop();
                ordering.push_back(cur);
                for (int j : adj[cur])	
                    if (--indegree[j] == 0)	
                        ready.push(j);
            }
            if (ordering.size() != adj.size())
                ordering.clear();	//There are cycles
            return ordering;
}


