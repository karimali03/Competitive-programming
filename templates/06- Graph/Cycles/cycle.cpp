int nxt[2*N];
int state[2*N]; 
bool cycle[2*N];
 
void init(int n){         
    f(i,0,n*2) nxt[i]=-1,state[i]=0,cycle[i]=false;
}
 
bool dfs(int u){
    if(state[u] == 1) return cycle[u] = true;
    if(state[u] == 2) return cycle[u];
    state[u] = 1;
    if(nxt[u] != -1) cycle[u] = dfs(nxt[u]);
    else cycle[u] = false;
    state[u] = 2;
    return cycle[u];
}
