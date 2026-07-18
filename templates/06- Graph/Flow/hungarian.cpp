/*
USE CASE:
- Solve the assignment problem: assign n workers to m jobs (m ≥ n) with minimum or maximum total cost.
- Input: cost matrix A[n][m] where A[i][j] is the cost of assigning worker i to job j.
- Output: matching of workers to jobs (each worker to exactly one job), minimizing (or maximizing) total cost.

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
pair<int, vector<int>> hungarian(vector<vector<int>>& a) {
    const int INF = 1e18; //  obviously greater than all numbers in a 
    int n = a.size();
    vector<int> u(n+1), v(n+1), p(n+1), way(n+1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        vector<int> minv(n+1, INF);
        vector<bool> used(n+1, false);
        int j0 = 0;
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1 = -1;
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = a[i0-1][j-1] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta) delta = minv[j], j1 = j;
                }
            }
            if (j1 == -1) {
                return {-1, vector<int>()};
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> ans(n);
    for (int j = 1; j <= n; ++j) ans[p[j]-1] = j-1;
    return { -v[0], ans };
}
