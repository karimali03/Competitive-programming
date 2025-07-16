const int N = 300005;
vector<int> adj[N];
int tin[N], low[N], timer;
int comp[N], comp_cnt;
stack<int> st;
bool on_stack[N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        tin[i] = low[i] = -1;
        comp[i] = -1;
        on_stack[i] = false;
    }
    while (!st.empty()) st.pop();
    timer = comp_cnt = 0;
}

void dfs(int v) {
    tin[v] = low[v] = timer++;
    st.push(v);
    on_stack[v] = true;

    for (int u : adj[v]) {
        if (tin[u] == -1) {
            dfs(u);
            low[v] = min(low[v], low[u]);
        } else if (on_stack[u]) {
            low[v] = min(low[v], tin[u]);
        }
    }

    if (low[v] == tin[v]) {
        while (true) {
            int u = st.top(); st.pop();
            comp[u] = comp_cnt;
            on_stack[u] = false;
            if (u == v) break;
        }
        comp_cnt++;
    }
}
