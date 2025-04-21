// Note: Transforming Linear DP to Matrix Exponentiation
// This problem counts strings of length n over m characters with k forbidden transitions.
// A DP approach uses dp[i][j] = sum(dp[i-1][k]) for all allowed k->j transitions (mx[k][j] = 1), costing O(n*m^2).
// For large n (up to 10^18), we use a matrix mx[m][m] where mx[i][j] = 1 if i->j is allowed, else 0:
//     [ S_1(n) ] = [ mx[0][0] mx[0][1] ... mx[0][m-1] ] [ S_1(n-1) ]
//     [ S_2(n) ]   [ mx[1][0] mx[1][1] ... mx[1][m-1] ] [ S_2(n-1) ]
//     [  ...   ]   [       ...                   ] [   ...     ]
//     [ S_m(n) ]   [ mx[m-1][0] ... mx[m-1][m-1] ] [ S_m(n-1) ]
// S_j(n) is the number of strings of length n ending in j. Compute mx^(n-1) * [1,1,...,1] in O(m^3 log n).
// Example 1 (2D DP): Like this problem, dp[i][j] counts strings with allowed transitions a[k][j] = 1.
// The matrix mx[i][j] = a[i][j] directly encodes transitions, optimized via exponentiation.
// Example 2 (1D DP): Consider dp[i] = dp[i-1] + dp[i-3] (e.g., ways to tile a 1xi board).
// Vectorize as [dp[i], dp[i-1], dp[i-2]], with matrix:
//     [ dp[i]   ] = [ 1 0 1 ] [ dp[i-1] ]
//     [ dp[i-1] ]   [ 1 0 0 ] [ dp[i-2] ]
//     [ dp[i-2] ]   [ 0 1 0 ] [ dp[i-3] ]
// First row [1, 0, 1] reflects dp[i] = dp[i-1] + dp[i-3]; other rows shift states (identity-like).
// Raising this to power i computes dp[i] in O(log i * 3^3), generalizing to any linear recurrence.

// Note: Fixed-Length Paths via Matrix Exponentiation (from cp-algorithms.com/graph/fixed_length_paths.html)
// Given a graph with n vertices and adjacency matrix G where G[i][j] = 1 if edge i->j exists, we can count paths of length k.
// For k=1, G gives paths of length 1. For k>1, compute G^k: entry (G^k)[i][j] is the number of paths from i to j of length k.
// Matrix multiplication iteratively builds C_{k+1}[i][j] = sum(C_k[i][p] * G[p][j]), summing paths via intermediate vertices.
// Using binary exponentiation, compute G^k in O(n^3 log k). In this problem, mx^(n-1) counts strings as paths of length n-1.
// Similarly, for shortest paths of length k in a weighted graph, modify multiplication to take min(G[i][p] + G[p][j]).

using mat = vec<vec<ll>>;
const int mod = 1'000'000'007;
mat product(const mat& a, const mat& b) {
    int n = a.size(), m = b[0].size(), p = b.size();
    mat ret(n, vi(m, 0));
    for(int i = 0 ;i < n ; i++){
        for(int k = 0 ;k < p ; k++){
            ll aik = a[i][k] % mod; 
            if (aik == 0) continue;
            for(int j =0 ;j < m ; j++){
                ret[i][j] += aik * b[k][j];
                if (ret[i][j] >= mod) ret[i][j] %= mod; 
            }
        }
    }
    return ret;
}

mat expo(mat &a , int k){
    int n = a.size();
    mat res(n,vi(n));
    for(int i = 0 ; i  < n ; i++) res[i][i] = 1; // identity matrix
    while(k>0){
        if(k&1) res = product(res,a);
        a = product(a,a);
        k>>=1;
    }
    return res;
}




// apply permutation k times 
vector<int> applyPermutation(vector<int> sequence, vector<int> permutation) {
    vector<int> newSequence(sequence.size());
    for(int i = 0; i < sequence.size(); i++) {
        newSequence[i] = sequence[permutation[i]];
    }
    return newSequence;
}

vector<int> permute(vector<int> sequence, vector<int> permutation, long long k) {
    while (k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        k >>= 1;
    }
    return sequence;
}
