/*
 * Template: Tree DP with Knapsack Merge (O(N^2))
 * Solves problems requiring selecting a subset of k nodes from a tree
 * where a node's cost/value depends on the parent's state.
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5005; // Max number of nodes
const ll INF = 1e18; // Represents infinity

int n;              // Number of nodes
ll budget;          // Max budget (if applicable)
vector<int> adj[N]; // Adjacency list for the tree
int sz[N];          // sz[u] = size of the subtree rooted at u

/*
 * DP STATE:
 * dp[u][k][state] = Minimum cost to select 'k' nodes from the subtree
 * rooted at 'u'.
 *
 * 'state' = 0: Node 'u' is NOT selected (or pays its 'base' cost)
 * 'state' = 1: Node 'u' IS selected (and gets a 'discount' / 'special' cost)
 *
 * Adjust the meaning of 'state' based on your problem.
 * You might need more states (e.g., parent not selected, parent selected).
 * The provided solution used a slightly different state, this is one common way.
 */
ll dp[N][N][2];
ll temp_dp[N][2]; // Temporary table for the knapsack merge

/* [Problem Specific] Input variables for node costs */
// Example:
int cost[N];
int discount[N];


void dfs(int u, int p = -1) {
    // 1. Initialize DP table for the base case (node u alone)
    sz[u] = 1;
    for (int i = 0; i <= n; ++i) {
        dp[u][i][0] = dp[u][i][1] = INF;
    }

    /* [Problem Specific] Set base cases for node u */
    // Example:
    dp[u][0][0] = 0; // Cost of selecting 0 nodes (not selecting u) is 0
    dp[u][1][0] = cost[u]; // Cost of selecting 1 node (u, at full price)
    dp[u][1][1] = cost[u] - discount[u]; // Cost of selecting 1 node (u, at discount)


    // 2. Recurse for all children
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);

        // 3. Knapsack Merge
        // Merge results from child 'v' into parent 'u'.
        // We use a temporary DP table to avoid using half-updated values.
        for (int i = 0; i <= sz[u] + sz[v]; ++i) {
            temp_dp[i][0] = temp_dp[i][1] = INF;
        }

        // Iterate over 'i' nodes from u's current state
        for (int i = 0; i <= sz[u]; ++i) {
            // Iterate over 'j' nodes from child v's state
            for (int j = 0; j <= sz[v]; ++j) {
                
                /* [Problem Specific] Define merge transitions */
                
                // Example Transition 1: u is in state 0 (not selected / full price)
                // Child 'v' MUST be in state 0 (full price)
                temp_dp[i + j][0] = min(temp_dp[i + j][0], dp[u][i][0] + dp[v][j][0]);

                // Example Transition 2: u is in state 1 (selected / discounted)
                // Child 'v' can be in *either* state.
                // We take the best (min) cost from v's subtree for j nodes.
                ll v_best = min(dp[v][j][0], dp[v][j][1]); 
                temp_dp[i + j][1] = min(temp_dp[i + j][1], dp[u][i][1] + v_best);
            }
        }

        // 4. Update subtree size and copy from temp table
        sz[u] += sz[v];
        for (int i = 0; i <= sz[u]; ++i) {
            dp[u][i][0] = temp_dp[i][0];
            dp[u][i][1] = temp_dp[i][1];
        }
    }
}

void solve() {
    // 1. Read Input
    cin >> n >> budget;
    for (int i = 1; i <= n; ++i) {
        /* [Problem Specific] Read node costs/discounts */
        // Example:
        cin >> cost[i] >> discount[i];
        if (i > 1) {
            int parent;
            cin >> parent;
            // Assuming 1-based indexing
            adj[parent].push_back(i);
            adj[i].push_back(parent); // Or not, if directed tree
        }
    }
    
    // For the second solution's format (parent is 0-indexed)
    /*
    for (int i = 0; i < n; ++i) {
        cin >> cost[i] >> discount[i];
        if (i > 0) {
            int parent;
            cin >> parent;
            adj[parent - 1].push_back(i); // Adjust indexing
        }
    }
    */


    // 2. Run the DP
    // Adjust root node as needed (e.g., 0 or 1)
    dfs(1); // Assuming root is 1
    // dfs(0); // If root is 0

    // 3. Find the answer
    int max_nodes = 0;
    // Iterate from largest k to smallest
    for (int k = n; k >= 0; --k) {
        /* [Problem Specific] Check final states at the root */
        // Example:
        ll final_cost = min(dp[1][k][0], dp[1][k][1]); // Root is 1
        
        if (final_cost <= budget) {
            max_nodes = k;
            break;
        }
    }

    cout << max_nodes << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t; // Uncomment for multiple test cases
    while (t--) {
        solve();
    }
    return 0;
}
