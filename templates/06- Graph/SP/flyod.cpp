/*
Time Complexity: O(n^3)
  - You need **all-pairs shortest paths**
  - Graph is dense (many edges: m ≈ n^2)
  - Graph size is small (n ≤ 500)
  - Graph has negative weights (but no negative cycles)
  - You want to **detect negative cycles** (check dist[i][i] < 0)
-> DON'T use Floyd-Warshall when:
  - Graph is **sparse** (m ≪ n^2): use Dijkstra or Bellman-Ford
Negative cycle detection:  for (int i = 0; i < n; ++i)  if (dist[i][i] < 0) → Negative cycle exists

*/
using ll = long long;

const ll INF = (ll)4e18;

struct Floyd {
    int n;

    vector<vector<ll>> dist;
    vector<vector<int>> nxt;

    Floyd(int n) : n(n) {
        dist.assign(n, vector<ll>(n, INF));
        nxt.assign(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
            nxt[i][i] = i;
        }
    }

    // Directed edge u -> v
    void add_directed(int u, int v, ll w) {
        // Important when multiple edges exist
        if (w < dist[u][v]) {
            dist[u][v] = w;
            nxt[u][v] = v;
        }
    }

    // Undirected edge u <-> v
    void add_undirected(int u, int v, ll w) {
        add_directed(u, v, w);
        add_directed(v, u, w);
    }

    // O(n^3)
    void run() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {

                if (dist[i][k] == INF)
                    continue;

                for (int j = 0; j < n; j++) {

                    if (dist[k][j] == INF)
                        continue;

                    ll nd = dist[i][k] + dist[k][j];

                    if (nd < dist[i][j]) {
                        dist[i][j] = nd;

                        // first node after i
                        // on the path i -> ... -> k -> ... -> j
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
        }
    }

    // Is v reachable from u?
    bool reachable(int u, int v) {
        return dist[u][v] != INF;
    }

    // Any negative cycle anywhere?
    bool has_neg_cycle() {
        for (int i = 0; i < n; i++)
            if (dist[i][i] < 0)
                return true;

        return false;
    }

    // Is there a negative cycle that can affect u -> v?
    bool neg_cycle_between(int u, int v) {
        for (int k = 0; k < n; k++) {
            if (
                dist[u][k] != INF &&
                dist[k][k] < 0 &&
                dist[k][v] != INF
            ) {
                return true;
            }
        }

        return false;
    }

    /*
        Path u -> v

        {} if:
        - unreachable
        - shortest path isn't finite because
          a negative cycle affects u -> v
    */
    vector<int> get_path(int u, int v) {
        if (nxt[u][v] == -1)
            return {};

        if (neg_cycle_between(u, v))
            return {};

        vector<int> path = {u};

        while (u != v) {
            u = nxt[u][v];

            if (u == -1)
                return {};

            path.push_back(u);
        }

        return path;
    }

    /*
        Mark all pairs affected by negative cycles as -INF.

        After calling:

        dist[u][v] == INF
            -> unreachable

        dist[u][v] == -INF
            -> arbitrarily small due to negative cycle

        otherwise
            -> finite shortest distance

        IMPORTANT:
        Call this AFTER run().
        Usually call it only after you're done using nxt/path reconstruction.
    */
    void mark_neg_inf() {
        vector<int> neg;

        for (int k = 0; k < n; k++) {
            if (dist[k][k] < 0)
                neg.push_back(k);
        }

        for (int k : neg) {
            for (int i = 0; i < n; i++) {
                if (dist[i][k] == INF)
                    continue;

                for (int j = 0; j < n; j++) {
                    if (dist[k][j] == INF)
                        continue;

                    dist[i][j] = -INF;
                }
            }
        }
    }
};
