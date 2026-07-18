const long long OO = 1e18; // Use a large enough value
const long long NEG_OO = -1e18;

struct edge {
    int from, to, w;
};

struct BellmanResult {
    vector<long long> dist;
    bool has_neg_cycle;
    vi cycle_path; // Empty if no cycle
};

BellmanResult BellmanFord(vector<edge> &edgeList, int n, int src) {
    vector<long long> dist(n, OO);
    vector<int> par(n, -1);
    dist[src] = 0;
    int x = -1; // Last updated node

    // PHASE 1: Standard Relaxation (N iterations)
    // We run N times. The N-th time is specifically to catch the cycle start node 'x'.
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const auto &ne : edgeList) {
            if (dist[ne.from] < OO) { // Ensure 'from' is reachable
                if (dist[ne.to] > dist[ne.from] + ne.w) {
                    // prevent underflow for normal calculation
                    dist[ne.to] = max(NEG_OO, dist[ne.from] + ne.w); 
                    par[ne.to] = ne.from;
                    x = ne.to;
                }
            }
        }
    }

    BellmanResult res;
    res.dist = dist; // Copy current state
    res.has_neg_cycle = (x != -1);

    // PHASE 2: Reconstruct the Negative Cycle (if one exists)
    if (x != -1) {
        // 1. Walk back N times to ensure we are INSIDE the cycle
        for (int i = 0; i < n; ++i) x = par[x];

        // 2. Walk the cycle to store it
        for (int v = x; ; v = par[v]) {
            res.cycle_path.push_back(v);
            if (v == x && res.cycle_path.size() > 1) break;
        }
        reverse(all(res.cycle_path));
    }

    // PHASE 3: Propagate -OO
    // If we found a cycle, we must mark ALL nodes reachable from it as -OO.
    // We run N-1 more iterations. If any node can be improved OR has a parent of -OO, it becomes -OO.
    if (x != -1) {
        for (int i = 0; i < n; ++i) {
            for (const auto &ne : edgeList) {
                if (dist[ne.from] < OO) {
                    if (dist[ne.to] > dist[ne.from] + ne.w || dist[ne.from] == NEG_OO) {
                        dist[ne.to] = NEG_OO;
                    }
                }
            }
        }
    }
    
    res.dist = dist; // Update with the propagated -OO values
    return res;
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    s--; // 0-based index

    vector<edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w});
    }

    BellmanResult res = BellmanFord(edges, n, s);

    // 1. Print Cycle if it exists
    if (res.has_neg_cycle) {
        cout << "Negative Cycle Found: ";
        for (int node : res.cycle_path) cout << node + 1 << " ";
        cout << "\n";
    } else {
        cout << "No Negative Cycle\n";
    }

    // 2. Print Distances
    cout << "Distances:\n";
    for (int i = 0; i < n; ++i) {
        if (res.dist[i] == OO) cout << i + 1 << ": Unreachable (*)\n";
        else if (res.dist[i] == NEG_OO) cout << i + 1 << ": Neg Cycle (-)\n";
        else cout << i + 1 << ": " << res.dist[i] << "\n";
    }
}
