#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;
const int K = 20; // Number of states: dp[i], dp[i-1], ..., dp[i-16]

// Multiply two KxK matrices
vector<vector<ll>> multiply(const vector<vector<ll>>& A, const vector<vector<ll>>& B) {
    vector<vector<ll>> C(K, vector<ll>(K, 0));
    for (int i = 0; i < K; ++i)
        for (int j = 0; j < K; ++j)
            for (int k = 0; k < K; ++k)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

// Matrix exponentiation
vector<vector<ll>> power(vector<vector<ll>> T, ll exp) {
    vector<vector<ll>> res(K, vector<ll>(K));
    for (int i = 0; i < K; i++) res[i][i] = 1;
    while (exp) {
        if (exp & 1) res = multiply(res, T);
        T = multiply(T, T);
        exp >>= 1;
    }
    return res;
}

// Precompute base dp values up to dp[16]
vector<ll> compute_base_dp() {
    vector<ll> dp(20, 0);
    dp[0] = 1;
    for (int i = 1; i <= 20; i++) {
        dp[i] = dp[i - 1];
        if (i >= 4)  dp[i] = (dp[i] + 3 * dp[i - 4]) % MOD;
        if (i >= 8)  dp[i] = (dp[i] + 3 * dp[i - 8]) % MOD;
        if (i >= 12) dp[i] = (dp[i] + 3 * dp[i - 12]) % MOD;
        if (i >= 16) dp[i] = (dp[i] + 3 * dp[i - 16]) % MOD;
    }
    return dp;
}

// Main function to get dp[n]
ll get_dp_n(int n) {
    vector<ll> base_dp = compute_base_dp();
    if (n < 20) return base_dp[n];

    // Create base state vector: [dp[16], dp[15], ..., dp[0]]
    vector<ll> base(K);
    for (int i = 0; i < K; i++) {
        base[i] = base_dp[16 - i];
    }

    // Build transition matrix T
    vector<vector<ll>> T(K, vector<ll>(K, 0));

    // First row corresponds to the recurrence
    T[0][0] = 1;
    T[0][6] = 3;
    T[0][10] = 3;
    T[0][14] = 3;
    T[0][18] = 3;

    // Shifting part: T[i][i-1] = 1
    for (int i = 1; i < K; i++) {
        T[i][i - 1] = 1;
    }

    // Raise T to the power (n - 16)
    vector<vector<ll>> T_n = power(T, n - 16);

    // Multiply T_n * base to get dp[n]
    ll result = 0;
    for (int i = 0; i < K; i++) {
        result = (result + T_n[0][i] * base[i]) % MOD;
    }
    return result;
}

int main() {
    int t; cin>>t;
    while(t--){
        int n;
        cin >> n;
        cout << get_dp_n(n) << "\n";
    }
    return 0;
}
