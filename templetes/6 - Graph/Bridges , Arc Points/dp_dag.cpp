// g[x] contains list of neighbors (edges from x -> it)
vector<int> dp(n, -1e9);

// ----------- From source to all points -----------
dp[src] = 0;
for (int x : topo) {
    dp[x] = max(dp[x], 0); // ensure initialization
    for (int it : g[x]) {
        dp[it] = max(dp[it], dp[x] + 1);
    }
}

// dp[x] = max path length from src to x
// ----------- From all points to target -----------
dp[target] = 0;
// reverse topo sort, or process in reverse
reverse(topo.begin(), topo.end());

for (int x : topo) {
    for (int it : g[x]) {
        if (dp[it] == -1e9) continue;
        dp[x] = max(dp[x], dp[it] + 1);
    }
}

// dp[x] = max path length from x to target

