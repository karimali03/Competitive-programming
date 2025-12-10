const double INF = 1e18; // Use a large enough value

struct Point {
    int x, y;
};

// Cost function (Modify based on problem: Euclidean, Manhattan, etc.)
double get_dist(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void solve() {
    int n;
    cin >> n;
    vector<Point> nodes(n);
    for (int i = 0; i < n; ++i) cin >> nodes[i].x >> nodes[i].y;

    // min_e[i] = shortest distance from MST to node i
    vector<double> min_e(n, INF);
    vector<bool> selected(n, false);
    
    min_e[0] = 0;
    double total_weight = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        // Find non-selected node with smallest distance to MST
        for (int j = 0; j < n; ++j) {
            if (!selected[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        }

        if (min_e[v] == INF) break; // Disconnected graph

        selected[v] = true;
        total_weight += min_e[v];

        // Update distances to neighbors
        for (int to = 0; to < n; ++to) {
            if (!selected[to]) {
                double dist = get_dist(nodes[v], nodes[to]);
                if (dist < min_e[to])
                    min_e[to] = dist;
            }
        }
    }

    cout << fixed << setprecision(9) << total_weight << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
