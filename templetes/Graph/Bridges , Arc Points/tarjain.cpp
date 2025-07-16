const int N = 300005;
vector<pair<int,int>> adj[N];
int low[N],tin[N];
bool is_bridge[N],is_arc[N];
int timer = 0;
void init(int n,int m){
    for(int i = 0 ; i < n ; i++){
        is_arc[i] = false;
        adj[i].clear();
        low[i] = 1e9; tin[i] = -1;
    }
    for(int i = 0 ; i < m ; i++) is_bridge[i] = false;
    timer = 0;
}
void tarjain(int v,int p){ // replace p with e is there are multi edges between two nodes
    low[v] = tin[v] = timer++;
    int kids = 0;
    for(auto [u,e] : adj[v]){ 
        if(u == p) continue;
        if(tin[u] != -1){ // back edge 
            low[v] = min(low[v] , tin[u]);
            continue;
        }
        tarjain(u,v); // tree edge 
        low[v] = min(low[v],low[u]);
        if(low[u] > tin[v]) is_bridge[e] = true;
        if(p != -1 && low[u] >= tin[v]) is_arc[v] = true;
        kids++;
    }
    if(p == -1 && kids > 1) is_arc[v] = true;
}

int id[N];
void bridge_tree(int v,int p , int x){
    id[v] = x;
    for(auto [u,e,z] : adj[v]){
        if(u == p) continue;
        if(is_bridge[e]) bridge_tree(u,v,u);
        else if(id[u] == -1) bridge_tree(u,v,x);
    }
}
