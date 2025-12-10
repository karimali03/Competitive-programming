// Note: Fixed-Length Paths via Matrix Exponentiation (from cp-algorithms.com/graph/fixed_length_paths.html)
// Given a graph with n vertices and adjacency matrix G where G[i][j] = 1 if edge i->j exists, we can count paths of length k.
// For k=1, G gives paths of length 1. For k>1, compute G^k: entry (G^k)[i][j] is the number of paths from i to j of length k.
// Matrix multiplication iteratively builds C_{k+1}[i][j] = sum(C_k[i][p] * G[p][j]), summing paths via intermediate vertices.
// Using binary exponentiation, compute G^k in O(n^3 log k). In this problem, mx^(n-1) counts strings as paths of length n-1.
// Similarly, for shortest paths of length k in a weighted graph, modify multiplication to take min(G[i][p] + G[p][j]).


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
