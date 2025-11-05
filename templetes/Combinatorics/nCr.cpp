// get nCr without taking mod.
ll nCrNoOverFlow(ll n, ll k) {
    if (n < k || k < 0) return 0;
    k = max(k, n - k);
    ll ans = 1;
    for (ll i = n; i > k; i--)
        ans = (ans * i) / (n - i + 1);
    return ans;
}

/**
 * dp solution to get 2d array of nCr.
 * C(n, k) = C(n - 1, k - 1) + C(n - 1, k).
 * C(n, 0) = C(n, n) = 1.
 * Time O(n * k).
 * Space O(n * k).
*/
vii binomialCoeff(int n, int k)
{
    vii C(n + 1, vi(k + 1));

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= min(i, k); j++)
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];

    return (C);
}
