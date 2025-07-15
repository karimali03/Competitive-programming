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
/*
Symmetry rule :  C(n,k) = C(n,n-k)
Factoring in :  C(n,k) = (n/k) C(n-1,k-1)
Sum over k : sum[k=0 -> n ]C(n,k) = 2^n
sum over n : sum[m=0 -> n ]C(m,k) = C(n+1,k+1)
sum over n and k : sum[k=0 -> m]C(n+k,k) = C(n+m+1,m)
sum of squares : C(n,0)^2 + C(n,1)^2 .... + C(n,n)^2 = C(2*n,n)
weighted sum : C(n,1) + 2*C(n,2) + 3*C(n,3) ... + nC(n,n) = n*2^n-1
Fib : C(n,0) + C(n-1,1) + ... + C(n-k,k) + .... + C(0,n) = F(n+1)
sum [j = 1 -> n ] { j * C(n-j,r) } = C(n+1,r+2)
*/
