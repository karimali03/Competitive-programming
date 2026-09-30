// Tree DP + Knapsack Merge
// dp[x] = answer using exactly x resources/items/nodes

const ll NEG = -(1LL << 60);

vi sz(n);

function<vector<ll>(int,int)> dfs = [&](int u, int p) -> vector<ll> {

    vector<ll> dp(k + 1, NEG);

    // -------------------------
    // Base case: node u alone
    // -------------------------

    dp[0] = 0;

    // Example if choosing u:
    // dp[1] = value[u];

    int cur = 0;
    sz[u] = 1;

    for (int v : g[u]) {
        if (v == p) continue;

        auto cdp = dfs(v, u);

        vector<ll> ndp(k + 1, NEG);

        // a = amount already taken
        for (int a = 0; a <= cur; a++) {

            if (dp[a] == NEG) continue;

            // b = amount taken from child v
            for (int b = 0;
                 b <= min(k - a, sz[v]);
                 b++) {

                if (cdp[b] == NEG) continue;

                // -------------------------
                // Knapsack Merge
                // -------------------------

                ndp[a + b] = max(
                    ndp[a + b],
                    dp[a] + cdp[b]
                );
            }
        }

        cur = min(k, cur + sz[v]);
        sz[u] += sz[v];

        dp.swap(ndp);
    }

    return dp;
};

/*
Sometimes `dp[u][amount]` is not enough because the parent needs extra information about node `u`.

Then use:  dp[state][amount]
or conceptually:  dp[u][state][amount]

Where:
* `amount` = knapsack/resource dimension
* `state` = information needed to connect subtree `u` with its parent

Examples of `state`:

* whether `u` is selected
* color/state of `u`
* number/value assigned to `u`
* whether an open path ends at `u`
* connectivity/component information

The merge is still the same idea: old_amount + child_amount = new_amount
but only combine compatible parent/child states.
Generic form:

```cpp
for (state_u)
    for (amount1)
        for (state_v)
            if (compatible(state_u, state_v))
                for (amount2)
                    ndp[state_u][amount1 + amount2] =
                        merge(
                            dp[state_u][amount1],
                            cdp[state_v][amount2]
                        );
```

Rule of thumb:

> `state` remembers what the parent needs to know.
> `amount` remembers what is being distributed among children.
*/
