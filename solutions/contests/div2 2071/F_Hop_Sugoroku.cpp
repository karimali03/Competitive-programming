#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;
const int N = 200005;
const int B = 500;

int n;
int v[N];
int dp[N];
int step[N][B];

void solve(int test_case) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> v[i];

    fill(dp, dp + N, 0);
    fill(&step[0][0], &step[N - 1][B - 1] + 1, 0);

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        // Apply all step updates for current index i
        for (int j = 1; j < B; j++) {
            dp[i] = (dp[i] + step[i][j]) % MOD;
            if (i + j < n) {
                step[i + j][j] = (step[i + j][j] + step[i][j]) % MOD;
            }
        }

        if (v[i] >= B) {
            // Direct simulation for large jump size
            for (int j = i + v[i]; j < n; j += v[i]) {
                dp[j] = (dp[j] + dp[i]) % MOD;
            }
        } else {
            // Use sqrt optimization for small jump size
            // step[i][v[i]] = (step[i][v[i]] + dp[i]) % MOD;
            if (i + v[i] < n) {
                step[i + v[i]][v[i]] = (step[i + v[i]][v[i]] + dp[i]) % MOD;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + dp[i]) % MOD;
    }

    cout << res << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
