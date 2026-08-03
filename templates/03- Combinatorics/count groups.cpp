/*
=============================================================================
O(K) COMBINATORICS: Pick subsets of size 2 or 3 from DIFFERENT groups
=============================================================================
Problem: Given an array of group sizes (ch), find the number of ways to pick 
2 or 3 items such that no two items come from the same group.

Naive: O(K^3) with nested loops or Generating Functions (Polynomials).
Optimal: O(K) using a running history state.

CRITICAL RULE: Always update in REVERSE order (triples -> pairs -> sum). 
If you update `sum` first, a group's elements will multiply against themselves, 
violating the rule that items must come from *different* groups.
=============================================================================
*/

// ch contains the sizes of the different groups/components
int sum = 0, pairs = 0, triples = 0;

for (int s : ch) {
    // 1. Triplets: This group (s) joins any valid pair formed by PREVIOUS groups
    triples += s * pairs; 
    
    // 2. Pairs: This group (s) joins any single item from PREVIOUS groups
    pairs += s * sum;     
    
    // 3. Sum: Add this group to the history pool for FUTURE groups to use
    sum += s;             
}

// Result:
// pairs   = total valid subsets of size 2
// triples = total valid subsets of size 3

/* 
GENERALIZATION FOR SIZE M (DP Approach):
vector<int> dp(M + 1, 0);
dp[0] = 1;
for (int s : ch) {
    for (int i = M; i >= 1; i--) {
        dp[i] += s * dp[i - 1];
    }
}
// dp[i] contains the number of valid subsets of size i.
*/
