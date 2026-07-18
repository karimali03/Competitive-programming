/*
====================== GRAPH STRUCTURES & CONNECTIVITY ======================

1. DFS Tree:
- A DFS tree is built during DFS traversal.
- Edge types:
    - Tree edge: discovered for the first time.
    - Back edge: goes to an ancestor → indicates a cycle.
    - Forward/cross edges: go to already visited nodes (non-ancestor).
- If the graph has **no bridges**, it is possible to assign directions 
  to the undirected edges such that the graph becomes **strongly connected**
  (i.e., every node can reach every other node).

2. Bridges:
- A **bridge** is an edge whose removal increases the number of connected components.
- If there's **only one path** from node `s` to `t`, then removing any edge or node 
  on that path will break connectivity.
- If there are **multiple paths**, only **bridge edges** can disconnect them.
- In DFS:
    - Use `tin[v]` (discovery time) and `low[v]` (lowest ancestor reachable).
    - An edge (v, to) is a bridge if: `low[to] > tin[v]`.

3. Weakly Connected Components (WCC) [Directed Graphs]:
- A WCC is a set of nodes that are connected **when ignoring directions**.
- Even if not all nodes in a WCC can reach each other in the directed graph,
  they form a single connected component in the undirected sense.
- WCCs help decompose the graph for processing reachability or connectivity
  when edge directions matter.
- For example, when adding minimum edges to make the graph strongly connected,
  WCCs must be handled independently.

4. Strongly Connected Components (SCC) [Directed Graphs]:
- An SCC is a maximal set of nodes such that:
    - For every pair (u, v) in the SCC: u → v and v → u exist.
- If SCC.size() > 1 → the component contains a **cycle**.
- If SCC.size() == 1 → it's a single node; may or may not be part of a cycle.
- The DAG formed by SCCs (condensation) is **acyclic**.
- Algorithms:
    - **Tarjan's Algorithm**: one DFS pass, uses low-link values and a stack.
    - **Kosaraju's Algorithm**: two DFS passes (original + reversed graph).

=============================================================================
*/

