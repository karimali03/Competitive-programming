
const int MAXV = 1005; // set according to problem constraints
const int INF = 1e9;

struct Dinic {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

    vector<Edge> adj[MAXV];
    int level[MAXV], ptr[MAXV];
    int s, t;

    void init(int _s, int _t) {
        s = _s;
        t = _t;
        for (int i = 0; i < MAXV; ++i)
            adj[i].clear();
    }

    void addEdge(int a, int b, int cap, bool directed = true) {
        adj[a].push_back({b, (int)adj[b].size(), cap, 0});
        adj[b].push_back({a, (int)adj[a].size() - 1, directed ? 0 : cap, 0});
    }

    bool bfs() {
        memeset(level,-1,sizeof(level));
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : adj[v]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int &i = ptr[v]; i < adj[v].size(); ++i) {
            Edge &e = adj[v][i];
            if (level[e.to] != level[v] + 1 || e.cap - e.flow == 0) continue;
            int tr = dfs(e.to, min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            e.flow += tr;
            adj[e.to][e.rev].flow -= tr;
            return tr;
        }
        return 0;
    }

    vector<vector<int>> min_cut() {
        vector<vector<int>> min;
        bool vis[MAXV]{};
        queue<int> q;
        q.push(s); vis[s] = true;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            for (auto it : adj[cur]) {
                if (!vis[it.to] && it.flow < it.cap) {
                    vis[it.to] = true;
                    q.push(it.to);
                }
            }
        }

        for (int i = 0; i < MAXV; ++i) {
            if (!vis[i]) continue;
            for (auto it : adj[i]) {
                if (it.cap > 0 && !vis[it.to]) {
                    min.push_back({i, it.to, it.cap});
                }
            }
        }

        return min;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            fill(ptr, ptr + MAXV, 0);
            while (int pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // Debug function to print the graph
    void printGraph(int n) {
        cout << "Graph (Node -> [To, Capacity, Flow]):\n";
        for (int i = 0; i < n; ++i) {
            if (adj[i].empty()) continue; // Skip nodes with no edges
            cout << "Node " << i << ": ";
            for (const auto &e : adj[i]) {
                if(e.cap>0)
                cout << "[" << e.to << ", " << e.cap << ", " << e.flow << "] ";
            }
            cout << "\n";
        }
        cout << "Source: " << s << ", Sink: " << t << "\n";
    }
};