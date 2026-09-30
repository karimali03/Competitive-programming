/*
 * Snippet: Sliding Window "Move" Function (Mo's Algorithm)
 *
 * This function safely moves the window from [current_l, current_r]
 * to [target_l, target_r].
 *
 * The order (Expand first, then Shrink) is crucial to prevent
 * an invalid state where l > r.
 */

// --- Global variables for the window state ---
int current_l = 0;
int current_r = -1; // Start with an empty window [0, -1]
long long current_answer = 0;
// int arr[N]; // Your data array
// long long freq[MAX_VAL]; // Example data structure

/**
 * Adds the element at 'index' to the window.
 * [Problem Specific]
 */
void add(int index) {
    // Example: add arr[index] to the current answer
    // freq[arr[index]]++;
    // current_answer += ...;
}

/**
 * Removes the element at 'index' from the window.
 * [Problem Specific]
 */
void remove(int index) {
    // Example: remove arr[index] from the current answer
    // freq[arr[index]]--;
    // current_answer -= ...;
}

/**
 * Moves the window to [target_l, target_r].
 * Uses the safe "Expand-then-Shrink" order.
 */
void move_window(int target_l, int target_r) {
    // 1. Expand
    while (current_l > target_l) add(--current_l); // Expand left
    while (current_r < target_r) add(++current_r); // Expand right

    // 2. Shrink
    while (current_l < target_l) remove(current_l++); // Shrink left
    while (current_r > target_r) remove(current_r--); // Shrink right
}
