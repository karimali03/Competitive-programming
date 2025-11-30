==============================================================================
         THE CP PROBLEM SOLVING PROTOCOL: A STRUCTURED FRAMEWORK
==============================================================================

[PHASE 0]: MENTAL SETUP
------------------------------------------------------------------------------
1. DO NOT TOUCH THE KEYBOARD YET.
2. Open your paper/whiteboard.
3. Remind yourself: "I am not looking for code. I am looking for a function."

==============================================================================
[PHASE 1]: INVESTIGATION & SIMULATION (THE "WHAT")
==============================================================================

A. DECODE THE STATEMENT
   - What is GIVEN? (Input type, constraints).
   - What is REQUIRED? (Min/Max, Count, Yes/No, Explicit Construction).
   - What are the OPERATIONS? (Swap, Add, Remove, Reverse).
   - [CRITICAL] Read the constraints carefully.
     - Are there "Fake Constraints"? (e.g., N is huge, but pattern loops at N=20).
     - Are there weird edge cases? (N=1, N=0).

B. ACTIVE SIMULATION (THE 5-SAMPLE RULE)
   - Do not just read the provided samples.
   - CREATE 5 CUSTOM SAMPLES and solve them manually on paper.
   - "Be the Computer": Execute operations strictly. Do not skip steps.
   - Reverse Engineer: Look at Input -> Output. Is the answer just (A + B)?
   - Symbolize: Stop using numbers. Use A, B, N, K. What is the relationship?

C. IDENTIFY PROPERTIES
   - Monotonicity: Does the answer only grow/shrink? (Binary Search hint).
   - Periodicity: Does the pattern repeat? (Modulo/Cycle detection).
   - Symmetry: Can I solve half and reflect it?
   - Parity: Do odd/even numbers behave differently?

==============================================================================
[PHASE 2]: COMPLEXITY BUDGET (THE "LIMITS")
==============================================================================

Look at Max N and determine your target Algorithm:

| Max N      | Target Time   | Likely Techniques                            |
|------------|---------------|----------------------------------------------|
| 10^18      | O(log N)      | Binary Search, Matrix Expo, Math Formula     |
| 10^8       | O(N)          | Greedy, Two Pointers, Prefix Sum, Hashing    |
| 4*10^7     | O(N log N)    | Sorting, Binary Search, Segment Tree, Set    |
| 10^4       | O(N^2)        | Standard DP, Shortest Path (Dense)           |
| 500        | O(N^3)        | Floyd-Warshall, 3D DP, Matrix Ops            |
| 90         | O(N^4)        | Heavy Pruning, Max Flow (sometimes)          |
| 40         | O(2^(N/2))    | Meet-in-the-Middle                           |
| 20         | O(2^N)        | Bitmask DP, Backtracking, Recursion          |
| 11         | O(N!)         | Permutations, Brute Force                    |

==============================================================================
[PHASE 3]: BRAINSTORMING STRATEGIES (THE "HOW")
==============================================================================

ASK THESE QUESTIONS TO UNBLOCK YOUR MIND:

1. FUNCTIONAL THINKING
   - Define f(State). What variables strictly define the current situation?
   - What is the transition? f(n) = f(n-1) + ...?

2. THE "NOISE" FILTER
   - What implies the answer?
   - Cross out details that don't affect the math (e.g., flavor text).
   - What is the core conflict?

3. REVERSE LOGIC
   - Work Backward: Start from the Goal State -> Initial State.
   - Binary Search the Answer: If I fix the answer to X, can I check if valid?
   - Complement: Is it easier to count (Total - Bad Cases)?

4. SIMPLIFICATION & ABSTRACTION
   - Graph: Is it really a graph? Or just components?
   - Math: Can I rewrite the formula? (e.g., (a+b)^2 expansion).
   - Constraints: What if N=1? What if the array is sorted?

5. CLASSIFICATION CHECKLIST
   - OPTIMIZATION? -> DP, Greedy, Binary Search on Answer, Dijkstra.
   - COUNTING? -> DP, Combinatorics, Matrix Expo.
   - DECISION (Yes/No)? -> Greedy, Graph Reachability, 2-SAT.
   - FIND ANY? -> Constructive, Greedy.

==============================================================================
[PHASE 4]: ALGORITHM SELECTION TOOLKIT
==============================================================================

[SEARCH]
- Binary Search (on answer or array)
- Ternary Search (unimodal functions)
- Meet-in-the-Middle (N=40)
- Two Pointers (Sliding Window)

[DYNAMIC PROGRAMMING]
- State? (Index, Mask, Count, Last Element)
- Transitions? (Take/Leave, Match/Skip)
- Optimization? (SOS DP, Matrix Expo)

[GRAPHS]
- Shortest Path: BFS (unweighted), Dijkstra (weighted positive), Bellman (negative).
- Connectivity: DFS, BFS, DSU (Union-Find).
- Tree Algos: LCA, Diameter, Rerooting.
- Flow: Max Flow / Min Cut (Bipartite Matching).

[DATA STRUCTURES]
- Range Queries: Segment Tree, BIT (Fenwick), Sparse Table.
- Ordered Data: Set, Map, Priority Queue.
- Strings: Trie, Hashing, KMP.

[MATH]
- Number Theory: GCD, LCM, Sieve, Prime Factorization.
- Combinatorics: nCr, Inclusion-Exclusion.
- Geometry: Convex Hull, Sweep Line.

==============================================================================
[PHASE 5]: VERIFICATION & DEBUGGING (THE "CHECK")
==============================================================================

BEFORE SUBMITTING:
1. "Did I remove the debug prints?"
2. "Did I use Long Long where necessary?" (Overflow check).
3. "Did I handle N=0 or N=1?" (Corner cases).
4. "Is my complexity within the table limits?"

IF WRONG ANSWER (WA):
1. Don't change random code.
2. Check your logic on the CUSTOM SAMPLES (Phase 1).
3. Is your Greedy assumption actually true? (Try to disprove it).
4. Did you clear global arrays between test cases?

IF TIME LIMIT EXCEEDED (TLE):
1. Check infinite loops.
2. Check complexity class (Are you doing O(N^2) when N=10^5?).
3. Are you creating new objects/vectors inside a tight loop?
4. Can you precompute values (Prefix Sums, Factorials)?

==============================================================================
[FINAL REMINDER]
KISS: Keep It Simple, Stupid.
If the solution requires 200 lines for a Div2 B problem, you are likely wrong.
Look for the simpler observation.
==============================================================================
