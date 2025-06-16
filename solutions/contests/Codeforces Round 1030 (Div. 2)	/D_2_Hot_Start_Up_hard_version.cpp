#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int ll
#define f(i, a, b) for (int i = a; i < b; i++)

const int K = 300010; // Safe buffer

int a[K], c[K], h[K], dp[K], mnk[K];
int n, k;

void init() {
    f(i, 0, n + 2) dp[i] = 1e17, a[i] = 0;
    f(i, 0, k + 2) mnk[i] = 1e17;
}

void solve() {
    cin >> n >> k;
    init(); 
    
    f(i, 0, n) cin >> a[i], a[i]--;
    a[n] = k; 
    
    f(i, 0, k) cin >> c[i];
    f(i, 0, k) cin >> h[i];
    c[k] = 0; 
    h[k] = 0;

    int def_ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i - 1] == a[i]) {
            def_ans += h[a[i]];
        } else {
            def_ans += c[a[i]];
        }
    }

    dp[0] = 0;
    int min_dp = 0;

    for (int i = 1; i <= n; i++) {
        int add_cost = (a[i] != a[i - 1] ? 0 : c[a[i]] - h[a[i]]);
        int option1 = min_dp;
        int option2 = mnk[a[i]] + h[a[i]] - c[a[i]];
      
        dp[i] = add_cost + min(option1, option2);

        min_dp = min(min_dp, dp[i]);
        mnk[a[i - 1]] = min(mnk[a[i - 1]], dp[i]);
    }

    cout << def_ans + dp[n] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
