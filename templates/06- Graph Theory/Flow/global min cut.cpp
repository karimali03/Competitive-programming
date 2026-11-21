// Global Minimum Cut - Stoer-Wagner O(V^3)
// Divide vertices into 2 nonempty groups, minimizing the sum of crossing edge weights.
//
// Ideas:
// - Minimum edges/cost to disconnect an undirected graph.
// - Split vertices into 2 groups with minimum separation penalty.
// - Find the weakest connection in a network (edge connectivity).
// - Find the minimum K such that removing edges of total cost K can disconnect the graph.
// - Contract vertices that must stay together before finding the cut.
//
// Difference:
// - Global Min Cut: choose ANY 2 nonempty groups (no fixed s, t).
// - S-T Min Cut: separate specific vertices s and t (use Max Flow).
// - Vertex Cut: remove vertices instead of edges.
// - Global Min Cut does NOT guarantee balanced group sizes.
//
// Notes: Undirected graph, nonnegative weights, missing edges = 0.
// Returns {minimum cut cost, vertices on one side}.

pair<int, vi> globalMinCut(vii mat) {
    pair<int, vi> best = {LONG_LONG_MAX, {}};
    int n = mat.size();
    vector<vi> co(n);
    for (int i = 0; i < n; i++) co[i] = {i};
    for (int ph = 1; ph < n; ph++) {
        vi w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) => O(E log V) with prio. queue
            w[t] = LONG_LONG_MIN;
            s = t, t = max_element(all(w)) - w.begin();
            for(int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        co[s].insert(co[s].end(), all(co[t]));
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = LONG_LONG_MIN;
    }
    return best;
}


