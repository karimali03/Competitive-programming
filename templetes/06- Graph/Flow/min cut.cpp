THE PROBLEM
- Goal: Choose binary S_i in {0, 1} for each item i to minimize total penalty.

PENALTIES
- S_i = 0: Pay cost A_i
- S_i = 1: Pay cost B_i
- S_i = 1 AND S_j = 0: Pay cost C_{i,j}

GRAPH CONSTRUCTION
- Nodes: Source (s) represents "1", Sink (t) represents "0".
- Edge s -> i: Capacity A_i
- Edge i -> t: Capacity B_i
- Edge i -> j: Capacity C_{i,j}

NEGATIVE COSTS (A and B)
- Add large constant M to A_i and B_i.
- Final Answer = MinCut - (n * M).

IMPORTANT
- C_{i,j} must be non-negative.
- Min Cut = Minimum Total Penalty.

ADVANCED MODELING TIPS

1. ALIGNING DEPENDENCIES (The 1->0 Rule)
   - The template strictly penalizes the "1 AND 0" state (Source -> Sink).
   - You must define 0 and 1 so that the *Forbidden State* maps to *1 and 0*.
   - Ex: If "Taking A implies Taking B":
     - Forbidden: Take A (1) AND Don't Take B (0).
     - Result: A is Source-side, B is Sink-side. Edge A -> B is INF.

2. PROFIT VS COST HEURISTIC
   - "Good" Items (Profit): Connect to Sink (t).
     - Logic: Cutting the edge means "Losing the Profit".
   - "Bad" Items (Cost): Connect to Source (s).
     - Logic: Cutting the edge means "Paying the Cost".
   - This often leads to nodes connecting to ONLY s or ONLY t (because the other option has 0 penalty).

3. CALCULATION TRICK
   - Result = (Sum of All Positive Profits) - Max Flow.

4. INTERACTION FLIPS (The "Both Chosen" Rule)
   - Problem: Penalty applies when A AND B are BOTH chosen.
   - Template constraint: Only penalizes 1 -> 0 (Source -> Sink).
   - Solution: Flip Set B definitions.
     - Set A: Chosen = 1 (Source)
     - Set B: Chosen = 0 (Sink)
   - Result: "Both Chosen" becomes "1 AND 0", creating a cuttable edge A -> B.

5. OVERLAP CORRECTION (Grid/Intersection Problems)
   - Context: Maximizing sum of Set A (Rows) + Set B (Cols).
   - Problem: Intersection items are counted twice.
   - Solution: Add edge Row_i -> Col_j with capacity = Intersection Value.
   - Logic: If both kept (1 -> 0), edge is cut -> we "pay back" the double count.
   - Note: If Intersection is Forbidden (Negative Value), Capacity = INF.
