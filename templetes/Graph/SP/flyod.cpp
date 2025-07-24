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
const int N = 505;
const int INF = 1e9;
int v[N][N], path[N][N];
int n, m;

void flyod() {
    f(i, 0, n) f(j, 0, n) v[i][j] = INF, path[i][j] = -1;
    f(i, 0, n) v[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; a--, b--;
        if (c < v[a][b]) {
            v[a][b] = v[b][a] = c;
            path[a][b] = path[b][a] = -1;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int relax = v[i][k] + v[k][j];
                if (relax < v[i][j]) {
                    v[i][j] = relax;
                    path[i][j] = k;
                }
            }
        }
    }
}


void build_path(int from, int to, vector<int> &road) {
    if (path[from][to] == -1) {
        road.push_back(from);
        if (from != to) road.push_back(to);
        return;
    }
    int mid = path[from][to];
    build_path(from, mid, road);
    road.pop_back();  
    build_path(mid, to, road);
}
