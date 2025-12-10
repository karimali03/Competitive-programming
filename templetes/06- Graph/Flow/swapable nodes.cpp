/*
 * ======================================================================================
 * EXPLANATION: SWAPPABLE NODES (Reachable Nodes)
 * ======================================================================================
 *
 * 1. WHAT IS A "SWAPPABLE NODE"?
 * --------------------------------------------------------------------------------------
 * A "Swappable Node" (often called a Reachable Node in Flow Theory) is a node that can 
 * eventually become "Free" (Unmatched) if we reshuffle the existing marriages.
 * * It falls into exactly one of these two categories:
 * Type A: The node is ALREADY Unmatched (Single).
 * Type B: The node is Matched (Married), but it is part of a chain that leads back 
 * to a Single node.
 * * Example:
 * Imagine Left_Node_1 is Single.
 * Imagine Left_Node_2 is Married to Right_Node_A.
 * If Left_Node_1 is connected to Right_Node_A, we can "Swap":
 * - Right_Node_A leaves Left_Node_2 and marries Left_Node_1.
 * - Now, Left_Node_2 becomes Free (Single).
 * Therefore, Left_Node_2 is "Swappable".
 * * Why do we need them?
 * Problem E asks to add ONE edge to increase matching.
 * To do this, we need to connect a "Swappable Left" to a "Swappable Right".
 * This creates a complete path: 
 * Single_Left ... -> Swappable_Left --(NEW EDGE)-- Swappable_Right <- ... Single_Right
 *
 * * 2. HOW DO WE GET THEM? (The Algorithm)
 * --------------------------------------------------------------------------------------
 * We use a Breadth-First Search (BFS) starting from all Single nodes.
 *
 * --- FINDING LEFT SWAPPABLE NODES ---
 * 1. Queue = Push all Unmatched Left Nodes.
 * 2. While Queue is not empty, pop node 'u'.
 * 3. Look at all neighbors 'v' (on the Right side).
 * 4. CRITICAL STEP: Don't stop at 'v'. Check who 'v' is currently matched with ('next_u').
 * 5. If 'next_u' exists and hasn't been visited:
 * - It means 'next_u' can pass its partner to 'u'.
 * - Mark 'next_u' as Swappable.
 * - Push 'next_u' to Queue.
 *
 * --- FINDING RIGHT SWAPPABLE NODES ---
 * (The logic is the exact mirror image)
 * 1. Queue = Push all Unmatched Right Nodes.
 * 2. While Queue is not empty, pop node 'v'.
 * 3. Look at all neighbors 'u' (on the Left side).
 * 4. CRITICAL STEP: Check who 'u' is currently matched with ('next_v').
 * 5. If 'next_v' exists and hasn't been visited:
 * - Mark 'next_v' as Swappable.
 * - Push 'next_v' to Queue.
 * * Final Answer = (Count of Left Swappable) * (Count of Right Swappable)
 * ======================================================================================
 */
