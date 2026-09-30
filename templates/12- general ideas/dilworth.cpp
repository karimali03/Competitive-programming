/*
======================================
          Dilworth's Theorem
======================================

In any finite poset (partially ordered set):
--> Minimum number of chains to cover all elements 
    = Size of the largest antichain.

--------------------------------------
1. Permutation Case:
--------------------------------------
- Define poset using "i < j && a[i] < a[j]"
- Chain  = Increasing Subsequence (LIS)
- Antichain = Decreasing Subsequence (LDS)

=> Minimum number of LIS to cover permutation = Length of LDS
=> Minimum number of LDS to cover permutation = Length of LIS

--------------------------------------
2. DAG Case:
--------------------------------------
- Define poset using "u < v if there's a path from u to v"
- Chain  = Path in DAG
- Antichain = Set of nodes with no paths between them

=> Minimum number of disjoint paths to cover all nodes = 
   Size of the largest antichain (independent set)

--------------------------------------
3. Grid Case (2D Points):
--------------------------------------
- Define poset using (x1, y1) < (x2, y2) if x1 < x2 && y1 < y2
- Chain  = Increasing sequence of 2D points
- Antichain = Set of points where no one dominates another

=> Minimum number of increasing chains to cover all points = 
   Size of the largest non-dominating set

--------------------------------------
Note:
- Used in problems involving scheduling, chain partition, or path cover.
- Related to König’s theorem and can be solved via max matching in DAG.

*/

