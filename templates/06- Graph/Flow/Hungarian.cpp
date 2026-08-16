/*
Hungarian — Assignment Problem
O(n^2 * m), usually O(n^3)

Requires:
    n <= m

Goal:
    match every LEFT vertex exactly once
    each RIGHT vertex used at most once
    minimize total cost

match[i] = right vertex assigned to left i

Maximum cost:
    negate all costs, run Hungarian, negate answer

Use Hungarian when:
    complete/dense bipartite assignment
    every left item must be assigned
    edge has cost


TYPICAL APPLICATIONS:
- Minimum Cost Perfect Matching in Bipartite Graphs
- Job Assignment / Task Scheduling
- Optimal Matching in Graphs with Weighted Edges
- Matching rows to columns based on preferences or distances

To MINIMIZE total cost:
    - Fill the cost matrix with actual costs.
    - For forbidden pairs, set cost[i][j] = INF (e.g. 1e9 or 1e15).
To MAXIMIZE total cost:
    - Fill the cost matrix with: cost[i][j] = -original_cost[i][j].
    - For forbidden pairs, still use a large positive INF (not -INF),
      so that those options are avoided.
*/
pair<ll, vector<int>> hungarian(vector<vector<ll>> a) {
    int n = a.size();
    int m = a[0].size();

    const ll INF = 4e18;

    vector<ll> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);

    for (int i = 1; i <= n; i++) {
        p[0] = i;

        int j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<bool> used(m + 1);

        do {
            used[j0] = true;

            int i0 = p[j0];
            ll delta = INF;
            int j1 = 0;

            for (int j = 1; j <= m; j++) {
                if (used[j]) continue;

                ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];

                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }

                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (int j = 0; j <= m; j++) {
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            }

            j0 = j1;

        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> match(n, -1);

    for (int j = 1; j <= m; j++)
        if (p[j])
            match[p[j] - 1] = j - 1;

    return {-v[0], match};
}
