int timer = 0;
int in[N], out[N];
vector<int> adj[N];

bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}


void dfs(int u, int parent) {
    in[u] = ++timer;
    for (int v : adj[u]) {
        if (v != parent)
            dfs(v, u);
    }
    out[u] = ++timer;
}
