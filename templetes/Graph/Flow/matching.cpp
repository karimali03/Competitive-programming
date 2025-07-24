/*
==================================================================
🧮 Bipartite Graph Algorithms Comparison Table
==================================================================

| Algorithm       | Goal                      | Type              | Time Complexity        | Use When...                                           |
|-----------------|---------------------------|-------------------|------------------------|--------------------------------------------------------|
| Hopcroft–Karp   | Max Matching              | Unweighted        | O(√V · E)              | - You need max cardinality matching                   |
|                 |                           |                   |                        | - Graph is unweighted                                 |
|-----------------|---------------------------|-------------------|------------------------|--------------------------------------------------------|
| Hungarian       | Min Cost Max Matching     | Weighted          | O(N³)                  | - Matching has costs/weights                          |
| (Kuhn–Munkres)  |                           |                   |                        | - Need optimal pairing with min total cost            |
|-----------------|---------------------------|-------------------|------------------------|--------------------------------------------------------|
| Dinic’s Algorithm| Max Flow (⇒ Max Matching) | Flow-based        | O(E√V) for unit cap     | - Need flexible modeling (capacities, constraints)    |
|                 |                           |                   | O(V²·E) general case    | - Part of a bigger flow/min-cut problem               |

==================================================================
🧠 Quick Tips:
- ✅ Hopcroft–Karp: Fastest for pure matching (unweighted)
- ✅ Hungarian: For assignment/cost optimization problems
- ✅ Dinic: When matching is embedded in flow logic or constraints
==================================================================
Minimum Vertex Cover :
It's the minimum number of nodes you need to pick to ensure that all connections (edges) are "covered" — i.e., no edge is left without one of its endpoints chosen.
In bipartie graph ( min vertex cover =  max matching )


*/

