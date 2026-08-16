========================= MIN CUT MODELING =========================

Max-Flow = Min-Cut

After maxflow:
    reachable from S using residual cap > 0 -> S side
    unreachable                            -> T side

A cut pays for every ORIGINAL edge:

        S-side  ----cost---->  T-side


-------------------------------------------------------------------
1) BINARY STATE
-------------------------------------------------------------------

Represent each variable/item x by one node.

    x on S side -> x = 1
    x on T side -> x = 0


-------------------------------------------------------------------
2) COST FOR ONE STATE
-------------------------------------------------------------------

Cost A if x = 0:
    
        S --A--> x

If x is on T side, this edge is cut -> pay A.


Cost B if x = 1:

        x --B--> T

If x is on S side, this edge is cut -> pay B.


So:

    cost(x=0) = A
    cost(x=1) = B

becomes:

    S -> x  cap A
    x -> T  cap B


-------------------------------------------------------------------
3) PAIR PENALTY: u = 1 AND v = 0
-------------------------------------------------------------------

Penalty C if:

    u = 1
    v = 0

Add:

    u --C--> v

Because this edge crosses the cut exactly when:

    u is S-side
    v is T-side

Main rule to remember:

    u -> v with capacity C
    =
    pay C when (u=1 && v=0)


-------------------------------------------------------------------
4) IMPLICATION / DEPENDENCY
-------------------------------------------------------------------

If:

    choose u => must choose v

Forbidden state:

    u = 1
    v = 0

So add:

    u --INF--> v

The minimum cut will never choose this forbidden state.


Examples:

    take project A => take project B
    select feature A => select dependency B

        A -> B (INF)


-------------------------------------------------------------------
5) MAXIMUM WEIGHT CLOSURE
-------------------------------------------------------------------

Each item has value w[i].

If w[i] > 0:
    choosing it gives profit w[i]

        S --w[i]--> i

If w[i] < 0:
    choosing it costs -w[i]

        i ---(-w[i])---> T


Dependencies:

    choose u => choose v

        u --INF--> v


Let:

    POS = sum of all positive values

Then:

    maximum profit = POS - maxflow


Why?

    We start with all positive profit.
    Min-cut finds minimum unavoidable loss/cost.


-------------------------------------------------------------------
6) MINIMUM COST TO DISCONNECT S AND T
-------------------------------------------------------------------

If edge e costs c[e] to remove:

    original graph edge capacity = c[e]

Then:

    min cost to disconnect S,T
    =
    minimum cut
    =
    maximum flow


To recover the cut after maxflow:

    vis = vertices reachable from S in residual graph

Cut edges are original edges:

    vis[u] = true
    vis[v] = false


-------------------------------------------------------------------
7) MINIMUM VERTEX CUT
-------------------------------------------------------------------

If removing vertex v costs c[v]:

Split it:

    v_in --c[v]--> v_out

Incoming edges -> v_in
Outgoing edges <- v_out

Now cutting:

    v_in -> v_out

means removing vertex v.

For minimum number of removed vertices:

    c[v] = 1


-------------------------------------------------------------------
8) EDGE-DISJOINT / VERTEX-DISJOINT PATHS
-------------------------------------------------------------------

Edge-disjoint paths:

    every original edge cap = 1

Then:

    maxflow
    =
    maximum edge-disjoint paths
    =
    minimum edges to remove to disconnect S,T


Vertex-disjoint paths:

    split every internal vertex:

        v_in --1--> v_out

Then:

    maxflow
    =
    maximum internally vertex-disjoint paths
    =
    minimum internal vertices to remove


-------------------------------------------------------------------
9) BIPARTITE MINIMUM VERTEX COVER
-------------------------------------------------------------------

Build matching flow:

    S -> Left -> Right -> T

all capacities = 1.

After maxflow:

    Z = nodes reachable from S in residual graph

Minimum Vertex Cover:

    unvisited LEFT
    +
    visited RIGHT

Konig:

    maximum matching size
    =
    minimum vertex cover size


-------------------------------------------------------------------
10) BOTH CHOSEN PENALTY
-------------------------------------------------------------------

Suppose penalty C happens when:

    A chosen AND B chosen

Min-cut naturally represents:

    1 -> 0

So sometimes flip the meaning of one group.

Example:

    Group A:
        chosen = 1

    Group B:
        chosen = 0

Then:

    A chosen AND B chosen
        becomes
    A = 1, B = 0

So add:

    A --C--> B

Useful when the problem naturally has two different groups.


-------------------------------------------------------------------
11) OVERLAP / DOUBLE COUNT CORRECTION
-------------------------------------------------------------------

Suppose choosing Row i gives profit
and choosing Column j gives profit,

but intersection (i,j) was counted twice.

If both are chosen, subtract value x.

Choose definitions so:

    Row chosen = 1
    Col chosen = 0

Then add:

    Row_i --x--> Col_j

If both are chosen, edge crosses cut -> pay x.

If that combination is forbidden:

    Row_i --INF--> Col_j


-------------------------------------------------------------------
12) MULTIPLE SOURCES / SINKS
-------------------------------------------------------------------

Multiple sources:

    SS -> source_i
    capacity = supply[i]

Multiple sinks:

    sink_i -> TT
    capacity = demand[i]

Then solve normal flow from:

    SS -> TT


-------------------------------------------------------------------
CORE MIN-CUT RULE
-------------------------------------------------------------------

Always ask:

    What does S-side mean?
    What does T-side mean?

Then remember:

    edge u -> v with capacity C
    penalizes exactly:

        u on S-side
        v on T-side

Everything else is built from this rule.
===================================================================
