/*
 Hierholzer’s Algorithm Template
 Works for both Directed and Undirected Graphs
 A Eulerian path is a path in a graph that passes through all of its edges exactly once. A Eulerian cycle is a Eulerian path that is a cycle.
  -------------------------------
 Requirements:
     For Undirected Euler Circuit:
         - All vertices have even degree
     For Undirected Euler Path:
         - Exactly 2 vertices have odd degree
     For Directed Euler Circuit:
         - For every vertex: in-degree == out-degree
     For Directed Euler Path:
         - Exactly one vertex with out-in = 1 (start)
         - Exactly one vertex with in-out = 1 (end)
     - Path lenght must be n + 1 where n in number of nodes
*/

vi vis;
vec<vec<pair<int,int>>>adj;
vi path; // reverse the path 
void dfs(int u){
    while(!adj[u].empty()){
        auto [v,id] = adj[u].back();
        adj[u].pop_back();
        if(vis[id]) continue;
        
        vis[id] = 1;
        dfs(v);
    }
    path.push_back(u);
}

