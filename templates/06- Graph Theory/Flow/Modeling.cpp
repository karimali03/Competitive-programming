===============================================================================
                    MIN-CUT MODELING — CONTEST NOTES
===============================================================================

Use these notes when a problem asks you to choose states / objects / colors /
projects and there are costs, rewards, dependencies, or pairwise interactions.

The main idea:

    Do NOT think first about "which edges should I cut?"

    Think:

        each graph node = one decision/state

        S-side = state 1
        T-side = state 0

Then translate every penalty into an edge.


===============================================================================
1) CORE RULE
===============================================================================

After maxflow(S,T):

    reachable from S in the residual graph   = S-side
    unreachable                              = T-side

A cut pays for every ORIGINAL directed edge:

    S-side ----C----> T-side

Therefore:

    u ----C----> v

means:

    pay C exactly when:

        u = 1
        v = 0


THIS IS THE MAIN RULE OF MIN-CUT MODELING.


===============================================================================
2) BASIC TRANSLATION RULES
===============================================================================

Let x be a binary variable.

-----------------------------------------------------------------------
A) Pay A if x = 0
-----------------------------------------------------------------------

Add:

    S ----A----> x

Reason:
    x=0 means x is on T-side, so S->x crosses the cut.


-----------------------------------------------------------------------
B) Pay B if x = 1
-----------------------------------------------------------------------

Add:

    x ----B----> T

Reason:
    x=1 means x is on S-side, so x->T crosses the cut.


-----------------------------------------------------------------------
C) Pay C if u = 1 and v = 0
-----------------------------------------------------------------------

Add:

    u ----C----> v


-----------------------------------------------------------------------
D) Enforce u = 1 => v = 1
-----------------------------------------------------------------------

The forbidden state is:

    u = 1
    v = 0

So add:

    u ----INF----> v


-----------------------------------------------------------------------
FOUR RULES TO MEMORIZE
-----------------------------------------------------------------------

    S -> x (A)
        pay A if x=0

    x -> T (B)
        pay B if x=1

    x -> y (C)
        pay C if x=1 and y=0

    x -> y (INF)
        enforce x=1 => y=1


===============================================================================
3) FIRST MODELING STEP: CHOOSE WHAT 0 AND 1 MEAN
===============================================================================

Do NOT always use:

    1 = chosen
    0 = not chosen

You may define the states however you want.

Before building the graph, write:

    S-side = ?
    T-side = ?

Examples:

    chosen / not chosen
    black / white
    enabled / disabled
    keep / delete
    buy / dont buy

Choose the meaning that makes important pair constraints look like:

    1 -> 0

because this is exactly what one directed cut edge represents.

Contest rule:

    If the model feels awkward, try flipping the meaning of 0 and 1.


===============================================================================
4) MAXIMUM PROFIT / MAXIMUM WEIGHT CLOSURE
===============================================================================

Suppose each item i has value w[i].

Use:

    1 = choose item
    0 = do not choose item


If w[i] > 0:

    choosing i gives profit w[i]

If we do NOT choose it, we lose that profit.

Add:

    S ----w[i]----> i


If w[i] < 0:

    choosing i costs -w[i]

Add:

    i ----(-w[i])----> T


If choosing u requires choosing v:

    u ----INF----> v


Let:

    POS = sum of all positive w[i]

Then:

    maximum profit = POS - mincut
                   = POS - maxflow


Quick rule:

    positive profit p:
        S -> item (p)

    choosing item costs c:
        item -> T (c)

    dependency u => v:
        u -> v (INF)

    answer:
        sum_positive - maxflow


===============================================================================
5) NEGATIVE UNARY COSTS
===============================================================================

Flow capacities cannot be negative.

Suppose:

    cost(x=0) = A
    cost(x=1) = B

and one of A,B is negative.

Choose M so that:

    A + M >= 0
    B + M >= 0

Replace:

    A = A + M
    B = B + M

Then build normally:

    S -> x (A)
    x -> T (B)

Every solution chooses exactly one state, so every solution gained the same +M.

Therefore:

    real answer = mincut - M

For many variables:

    real answer = mincut - sum(M[i])


IMPORTANT:

    This constant-shift trick works for unary costs because exactly one unary
    state is paid for every variable.

    It does NOT directly fix a negative pair penalty C for (u=1,v=0).


===============================================================================
6) FLIP ONE PARTITION
===============================================================================

Min-cut directly represents a penalty for:

    (1,0)

But sometimes the natural interaction is:

    penalty if (1,1)

If the interaction graph is bipartite, split the variables into:

    Left
    Right

Keep Left meaning normally:

    chosen = 1

Flip the meaning on Right:

    chosen = 0

Then:

    both chosen

becomes:

    Left = 1
    Right = 0

which is exactly the min-cut pair form.


Common triggers:

    rows <-> columns
    even parity <-> odd parity
    black cells <-> white cells
    two different object groups


Contest rule:

    If the bad/penalized state is "both chosen",
    check whether the interaction graph is bipartite.

    If yes, flip one partition.


===============================================================================
7) AUXILIARY / BONUS NODE
===============================================================================

Use an auxiliary node when a reward/event depends on several decisions.

Example:

    get reward C if x and y are both chosen

Create node z with meaning:

    z = 1  <=>  claim this reward

Give z profit C:

    S ----C----> z

To claim the reward, x and y must both be chosen:

    z => x
    z => y

So add:

    z ----INF----> x
    z ----INF----> y


Graph:

               C
    S -----------------> z
                        / \
                     INF   INF
                      /     \
                     v       v
                     x       y


General form:

    reward C if all prerequisites are chosen

Create z:

    S -> z (C)

Then:

    z -> prerequisite1 (INF)
    z -> prerequisite2 (INF)
    z -> prerequisite3 (INF)
    ...


Contest rule:

    reward/bonus if several conditions all hold
        ->
    create bonus node z
        ->
    z implies every prerequisite


===============================================================================
8) INTEGER VARIABLE -> THRESHOLD NODES
===============================================================================

Use this when:

    x in {0,1,...,K}

but min-cut nodes are binary.


-----------------------------------------------------------------------
A) Create threshold nodes
-----------------------------------------------------------------------

For every v = 1..K, create:

    T[v] = 1  iff  x < v

Example:

    x in {0,1,2,3}

    T1 = [x < 1]
    T2 = [x < 2]
    T3 = [x < 3]

Then:

    x = 0  -> 111
    x = 1  -> 011
    x = 2  -> 001
    x = 3  -> 000

The position where the bits change from 0 to 1 determines x.


-----------------------------------------------------------------------
B) Force valid / monotone states
-----------------------------------------------------------------------

If:

    x < v

then automatically:

    x < v+1

So:

    T[v] = 1 => T[v+1] = 1

Add:

    T[v] ----INF----> T[v+1]

for every:

    1 <= v < K


-----------------------------------------------------------------------
C) Penalty rules
-----------------------------------------------------------------------

Remember:

    T[v] = 1  iff  x < v
    T[v] = 0  iff  x >= v


Penalty C if x < v:

    T[v] ----C----> T


Penalty C if x >= v:

    S ----C----> T[v]


Penalty C if x = v, where 0 < v < K:

    x = v
    iff
    T[v]   = 0
    T[v+1] = 1

Add:

    T[v+1] ----C----> T[v]


Boundary values:

Penalty C if x = 0:

    T[1] ----C----> T


Penalty C if x = K:

    S ----C----> T[K]


-----------------------------------------------------------------------
D) Reward rules
-----------------------------------------------------------------------

Min-cut minimizes penalties.

Convert:

    reward C if condition

into:

    penalty C if condition is false

and subtract C from the final answer.


Reward C if x < v:

    false condition = x >= v

Add:

    S ----C----> T[v]

Then:

    answer -= C


Reward C if x >= v:

    false condition = x < v

Add:

    T[v] ----C----> T

Then:

    answer -= C


Reward C if x = v, where 0 < v < K:

The false cases are:

    x < v
    OR
    x >= v+1

These cases are disjoint.

Add:

    T[v] ----C----> T
    S ----C----> T[v+1]

Then:

    answer -= C


Boundary values:

Reward C if x = 0:

    false condition = x >= 1

Add:

    S ----C----> T[1]

Then:

    answer -= C


Reward C if x = K:

    false condition = x < K

Add:

    T[K] ----C----> T

Then:

    answer -= C


-----------------------------------------------------------------------
THRESHOLD QUICK RULES
-----------------------------------------------------------------------

Definition:

    T[v] = [x < v]

Monotonicity:

    T[v] -> T[v+1] (INF)


Penalty:

    x < v   -> T[v] -> T       (C)
    x >= v  -> S -> T[v]       (C)
    x = v   -> T[v+1] -> T[v]  (C)


Reward:

    reward if x < v
        -> S -> T[v] (C)
        -> answer -= C

    reward if x >= v
        -> T[v] -> T (C)
        -> answer -= C

    reward if x = v
        -> T[v] -> T (C)
        -> S -> T[v+1] (C)
        -> answer -= C


Mental model:

    integer variable
        ->
    one node per threshold
        ->
    INF edges force monotonicity
        ->
    cut position determines the value


===============================================================================
9) GRID / CHECKERBOARD FLIP
===============================================================================

Grid adjacency is bipartite:

    (i+j)%2 = 0
    (i+j)%2 = 1

If neighboring cells have a binary state/color and the natural penalty is for:

    same state
    both selected
    both black
    etc.

try flipping the state meaning on one parity.

Then many difficult pair conditions become:

    (1,0)

and can be represented by a directed edge.


Contest trigger:

    grid
    + binary state/color
    + neighbor interactions

Think:

    checkerboard partition
    + flip one side


===============================================================================
10) OVERLAP / DOUBLE-COUNT CORRECTION
===============================================================================

Typical case:

    choosing Row i gives some profit
    choosing Column j gives some profit

but choosing both double-counts the value at intersection (i,j).

Suppose the duplicated value is C.

Choose meanings so that:

    Row chosen = 1
    Column chosen = 0

Then "both chosen" becomes:

    Row = 1
    Column = 0

Add:

    Row_i ----C----> Col_j

This subtracts C exactly when both are selected.


If choosing both is forbidden instead of merely penalized:

    Row_i ----INF----> Col_j


===============================================================================
11) MINIMUM COST TO DISCONNECT S AND T
===============================================================================

If removing edge (u,v) costs C:

    use edge capacity C

Then:

    minimum cost to disconnect S,T
    =
    minimum cut
    =
    maximum flow


After maxflow:

    reachable from S in residual graph   = source side
    unreachable                          = sink side

The original edges:

    reachable -> unreachable

form a minimum cut.


===============================================================================
12) VERTEX CAPACITY / MINIMUM VERTEX CUT
===============================================================================

Normal flow puts capacities on edges.

If using/removing vertex v has capacity/cost C, split it:

    v_in ----C----> v_out

Redirect:

    all original incoming edges -> v_in
    all original outgoing edges <- v_out

Now cutting:

    v_in -> v_out

means paying for/removing vertex v.


For minimum number of removed vertices:

    C = 1


===============================================================================
13) EDGE-DISJOINT / VERTEX-DISJOINT PATHS
===============================================================================

-----------------------------------------------------------------------
A) Edge-disjoint paths
-----------------------------------------------------------------------

Set every original edge capacity to 1.

Then:

    maxflow
    =
    maximum number of edge-disjoint S->T paths

By max-flow min-cut:

    maximum edge-disjoint paths
    =
    minimum number of edges to remove to disconnect S,T


-----------------------------------------------------------------------
B) Vertex-disjoint paths
-----------------------------------------------------------------------

Split each internal vertex:

    v_in ----1----> v_out

Then:

    maxflow
    =
    maximum number of internally vertex-disjoint S->T paths

By max-flow min-cut:

    maximum vertex-disjoint paths
    =
    minimum number of internal vertices to remove


===============================================================================
14) BIPARTITE MINIMUM VERTEX COVER
===============================================================================

Build matching flow:

    S -> Left -> Right -> T

All capacities = 1.

After maximum matching / maxflow:

    Z = vertices reachable from S in the residual graph

Then:

    Minimum Vertex Cover
    =
    unvisited LEFT
    +
    visited RIGHT


Konig:

    maximum matching size
    =
    minimum vertex cover size


===============================================================================
15) MULTIPLE SOURCES / MULTIPLE SINKS
===============================================================================

If there are many sources, create super source SS:

    SS -> source_i

capacity:

    supply[i]
    or INF if unlimited


If there are many sinks, create super sink TT:

    sink_i -> TT

capacity:

    demand[i]
    or INF if unlimited


Then solve normal maxflow:

    SS -> TT


===============================================================================
16) CONTEST MODELING PROCEDURE
===============================================================================

STEP 1) Define the states.

    Write explicitly:

        S-side = ?
        T-side = ?


STEP 2) Rewrite every cost/constraint using binary states.

Try to express it as one of:

    pay A if x=0
    pay B if x=1
    pay C if x=1,y=0
    forbid x=1,y=0


STEP 3) Translate mechanically.

    x=0 cost A:
        S -> x (A)

    x=1 cost B:
        x -> T (B)

    x=1,y=0 cost C:
        x -> y (C)

    x=1 => y=1:
        x -> y (INF)


STEP 4) If the pair condition does not fit (1,0), try:

    1. flip the meaning of 0/1

    2. if interactions are bipartite:
           flip one partition

    3. if a reward depends on several prerequisites:
           add an auxiliary bonus node

    4. if a variable is a small integer:
           use threshold nodes


STEP 5) Make all capacities nonnegative.

    Negative unary costs:
        shift both unary states by a constant
        subtract that constant from the final answer


STEP 6) Run maxflow.


STEP 7) Recover the chosen states if needed.

    reachable from S in residual graph:
        state = 1

    unreachable:
        state = 0


===============================================================================
17) FINAL MEMORY BOX
===============================================================================

If you forget everything else, remember:

    S-side = 1
    T-side = 0

    S -> x (A)
        pay A if x=0

    x -> T (B)
        pay B if x=1

    x -> y (C)
        pay C if x=1 and y=0

    x -> y (INF)
        enforce x=1 => y=1


Then derive the rest by choosing good meanings for 0 and 1.
===============================================================================