PROBLEM ANALYSIS & INPUT UNDERSTANDING
1. Problem Statement
- Read carefully and slowly.
- Mark important details: operations, conditions
- what is given and what is required ?
- Understand input format, constraints, and output requirements.
- Re-read long problems after initial pass for full clarity.
- Weird/edge-case constraints often hint at tricky logic.

2. Sample Test Cases
- Trace all sample inputs manually.
- try 5 samples on your own ( simulate process )
- Check boundaries, off-by-one, and missing cases.

3. Input Properties
- Overflow risks: factorials, powers, large products.
- Precision issues: floating point divisions.
- Graph characteristics:
  - Complete / Tree / DAG / Bipartite
  - Directed / Undirected / Self-loops / Multi-edges
- Hidden properties: 
    - monotonicity : only increases or only decreases as input increases.
    - periodicity : A function or pattern repeats itself after a certain interval.
    - symmetries : You can reduce work by solving just one side and reflecting the result.  

4. Constraint-Based Complexity Guidelines
| Max N     | Target Complexity | Techniques                                   |
|-----------|-------------------|----------------------------------------------|
| 1e18      | O(log N)          | Binary/Ternary Search, Matrix Expo, DSU Ops  |
| 1e8       | O(N)              | Prefix Sum, Greedy, Two Pointers             |
| 4e7       | O(N log N)        | Sort, Binary Search, Segment Tree, D&C       |
| 1e4       | O(N^2)            | DP, Ad-hoc, Greedy                           |
| 500       | O(N^3)            | Matrix Ops, 3D DP, Floyd-Warshall            |
| 90        | O(N^4)            | Heavy pruning needed                         |
| 50        | ~Exponential      | Smart brute-force, Pruned Recursion          |
| 40        | O(2^(N/2))        | Meet in the Middle                           |
| 20        | O(2^N)            | Backtracking, Bitmask DP                     |
| 11        | O(N!)             | Permutations, Orderings                      |

5. Fake Constraints (Trap Cases)
- Large bounds may be fake; real logic may collapse quickly.
- Example: rightmost digit of n! is 0 for all n ≥ 5.
- Some functions become constant after a point.
  - Example: F(n) for n ≥ 20 → constant → brute small n.
- GCD sets often contain ≤ 30 distinct values.
NVESTIGATE THE PROBLEM

1. Solution Space Analysis
- What is the type of problem? (Optimization, Decision, Counting…)
- What are the bounds? Can it be brute-forced?
- Can the problem be reformulated algebraically or as a recurrence?

2. Domain Identification
- Is the problem best viewed as:
  - Graph-based? (nodes/edges, flow, connectivity)
  - Geometrical? (angles, distances, coordinates)
  - Number theory? (gcd, mod, divisibility)
  - String-based? (patterns, prefixes, hashes)

3. Similar Problems
- Have you seen a similar problem?
- Could this be a misleading variant of a classic one?
- Consider known patterns with twists (e.g., reversed prefix sums, rotated matrix)

4. Abstraction
- Can you generalize or abstract the problem?
- What are the core objects and operations?
- Can you map this to a known problem class?

5. Search Space Investigation
- What is the state of brute-force?
  - How many decisions?
  - Is it exponential or polynomial?
  - Can you reduce it?
- Can you apply early pruning, memoization, or state compression?

6. Draw and Visualize
- Draw graphs, arrays, grids, or state transitions
- Mark known/unknown values, relations, or movement
- Reformulate constraints into visual/geometric space

7. Reverse or Simplify
- Think backwards: can you reverse the steps?
- Can you simplify:
  - Fixed values?
  - Base cases?
  - Reduced sub-version?
THINK
1. Think on Paper
- Do NOT rush to code.
- Use pen and paper to brainstorm, write equations, try examples.

2. Think Concretely & Symbolically
- Try small fixed values to understand behavior.
- Express with variables, recurrence relations, or formulas.

3. Think Divide & Conquer
- Break down the problem into manageable sub-problems.
- Can it be split recursively or by structure?

4. Think Forward & Backward
- Try solving from input → output (forward).
- Also try from output → input (reverse logic).

5. Think With or Without Known Algorithms
- Dont force-fit a known algorithm.
- Ask: What happens *without* it? Any natural structure emerges?

6. Observations
- Spot patterns, monotonicity, periodicity, invariants.
- Use the PC if it helps automate observation quickly (e.g., brute + print pattern).

7. KISS  Keep It Simple, Stupid
- Dont overcomplicate.
- Simple ideas with strong pruning or clever observation often beat complex ones.

8. Problem or Sub-problem?
- Are you solving the full problem or just a component?
- Can subproblems lead to full solution via DP, recursion, greedy?

9. Rank and Attack Ideas
- List ideas, approaches, and observations.
- Rank by feasibility, complexity, or intuition.
- Start attacking the top candidate.

10. Guess & Check
- If stuck, try a bold guess or greedy approach.
- Implement/check it on paper for small inputs.
- Refine based on failure or pattern revealed.

SOLVE
1. Found a Solution? Any Simpler?
- Ask: Can I simplify it?
- Is there a cleaner or more intuitive way?
- Remove unnecessary logic, variables, or steps.

2. Solution Verification

-- Test Case Verification
- Run through sample and custom test cases by hand or code.
- Include edge cases, stress cases, corner cases.

-- Logic & Correctness
- Intuitively or formally verify correctness.
- Prove greedy choices, recurrence validity, or structure integrity.

-- Time & Space Complexity
- O(time), O(memory), recursion depth (if recursive).
- Will it pass all constraints?

-- Look-back Verification
- Rethink the original problem.
- Does the solution fully solve it? Any condition missed?

3. Solution Fails?
- Was your thinking flawed? Go back to idea stage.
- Was implementation flawed? Debug carefully.
- Dont patch — fix the core issue.

BIG ORDER — OPTIMIZING AND SIMPLIFYING

1. Big-O Estimate
- Approximate total # of operations.
- Is the solution within acceptable time for max N?

2. Reduced Variables
- Eliminate unused or unnecessary variables.
- Collapse dimensions when possible (e.g., 3D → 2D → 1D).

3. Reference Locality
- Cache-friendly iteration (row-wise in arrays, etc.).
- Improve constant factors by memory-friendly access.

4. Clever Tricks
- Bit hacks, prefix XORs, difference arrays, etc.
- Encode multiple states/values into one variable when safe.

5. Precomputation
- Full or partial?
  - Full table: factorials, power tables, dp[].
  - Partial (range queries): prefix sums, sparse tables, etc.
- Preprocessing:
  - Sort data, build maps, compress values before main logic.

6. Simplifications
- Adhoc simplification: apply direct transformations to reduce input size or complexity.
- Map general N → ordered form: 1, 2, ..., N.
- Reduce higher-dimensional problems:
  - 2D → 1×1, 1×2, 2×1, 1×N
  - 3D → 2D → 1D
- Break down structures:
  - Polygon → Convex → Triangle
  - N players → 1v1, then generalize
  - Graph → DAG → Tree → Chain
- Compress space:
  - Big rectangle → compressed coordinates.
- Convert base:
  - Use base 10, prime bases, or digit dynamic programming.
  - Map from base X → manageable format.

7. Reverse Logic & Rewriting
- Adhoc reversing (e.g., value → index).
- Binary Search on answer (searchable X through function Y = F(X)).
- Reverse relations:
  - Given Y = F(X), deduce X if function is monotonic/searchable.

8. Property Reversal Tricks
- MinSum = TotalSum – MaxSubSum
- Subsets with value X = Total subsets – Subsets without X
- P(X) = 1 – P(not X)

OPTIMIZATION
-------------
Common:
- Fake/DFS
- DP / Greedy / Brute Force
- Binary Search / Ternary Search
- Branch & Bound
- RMQ / LCA
- Line Sweep
- AlgoX

Minimization:
- MCMF
- Min cut / vertex
- MST / Dijkstra
- Convex Hull / Min Enclosing Circle

Maximization:
- Max Flow / MCMF
- Max Independent Set
- Kruskal Reverse
- LIS / GCD

SEARCH ALGORITHMS
------------------
- BFS / DFS / ID-dfs
- Backtracking
- Binary Search / Ternary Search
- Golden Ratio
- Meet in Middle
- Divide & Conquer
- Branch & Bound
- Min Enclosing Circle

DP (DYNAMIC PROGRAMMING)
-------------------------
General:
- State representation(s)
- Diff sub-states calls?
- Move to state
- Cycles?
- Depth?
- Dijkstra / BFS
- Dec(resent)-inc-dec patterns

Types:
- Restricted / Range
- Counting
- Tree / Partitioning
- Extending table

Concerns:
- Base case order
- Search space?
- Constrained params
- Redundant parts
- Small canonical states?
- Local Minima
- Small subsets count?
- Large pads?
- Reduces fast? (e.g., /, log)

Counting Problems:
- DP
- Combinations / Permutations
- Inclusion-Exclusion
- Graph Power

DATA STRUCTURES
----------------
- Set/Heap/Disjoint Sets
- BIT
- Segment Tree
- Treap, KDT
- LCA / RMQ
- Hashing
- Interval Compression
- Quad Tree

GRAPH ALGORITHMS
-----------------
- MST: Kruskal / Prime
- Dijkstra / Topological
- Convex Hull / Floyd
- Max Flow / Min Cut
- Max Matching
- Max Indep Set
- Min path/vertex cover
- Bellman / DConns
- Euler / Postman

STRING ALGORITHMS
------------------
- Permutation Cycles
- Tries
- LCS / LIS
- Polynomial Hashing
- KMP / Aho Corasick
- Suffix Tree / Array

MATHEMATICS
------------
- GCD / LCM / Phi / Mobius
- BIT
- NIM / Grundy / Chinese
- Sieve / Factorization
- System of Linear Equations
- Determinant
- Simplex / Pick’s Theorem
- Numerical Integration
- Matrix Power
- Closed Form
- Pigeon Hole
- Triangle Inequality
- Voronoi Diagram

ADHOC ALGORITHMS
-----------------
- Greedy
- Line Sweep
- Sliding Window
- Canonical Form
- Grid Decompositions
- Constructive Algorithms
- State Guess
- Randomization
- Time-case driven
- Stress Test & Observe

DECISION ALGORITHMS
---------------------
- 2SAT
- Difference Constraints
- Grundy
- Bipartite?