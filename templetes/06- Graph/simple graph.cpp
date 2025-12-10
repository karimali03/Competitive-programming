#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to check if a sequence of degrees can form a simple graph
bool is_valid_simple_graph(vector<int> degrees) {
    int n = degrees.size();
    if (n == 0) return true;

    // Check 1: Negative degrees are impossible
    // Check 2: Sum of degrees must be even (Handshaking Lemma)
    long long sum_deg = 0;
    for (int d : degrees) {
        if (d < 0) return false;
        sum_deg += d;
    }
    if (sum_deg % 2 != 0) return false;

    // Check 3: Sort descending (Crucial for Erdős-Gallai)
    // Time Complexity: O(N log N)
    sort(degrees.rbegin(), degrees.rend());

    // Check 4: Create Prefix Sum array
    // Time Complexity: O(N)
    // pref[i] holds the sum of degrees[0...i-1]
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + degrees[i];
    }

    // Check 5: Iterate through k = 1 to n
    // Time Complexity: O(N) using the Moving Pointer technique
    int bound = n - 1; 
    
    for (int k = 1; k <= n; ++k) {
        // LHS: Sum of the k largest degrees
        long long lhs = pref[k];

        // RHS Calculation
        // We need to calculate: k*(k-1) + sum(min(d_i, k)) for i > k
        // The sum splits into two parts:
        // 1. Nodes where d_i >= k (contribute k)
        // 2. Nodes where d_i < k  (contribute d_i)
        
        // Adjust 'bound' pointer to find the split point.
        // 'bound' is the rightmost index where degrees[bound] >= k.
        // Since k increases, the condition is stricter, so bound moves left (monotonic).
        while (bound >= k && degrees[bound] < k) {
            bound--;
        }

        // Ensure bound doesn't bleed into the top k nodes
        int split_idx = max(k - 1, bound);

        // Part A: Max connections among the top k nodes
        long long term1 = (long long)k * (k - 1);

        // Part B: Connections from top k to remaining nodes with degree >= k
        // Count of such nodes is (split_idx - (k - 1))
        long long count_high = split_idx - (k - 1);
        long long term2_high = count_high * k;

        // Part C: Connections from top k to remaining nodes with degree < k
        // Sum of degrees from split_idx + 1 to end
        long long term2_low = pref[n] - pref[split_idx + 1];

        if (lhs > term1 + term2_high + term2_low) {
            return false;
        }
    }

    return true;
}

int main() {
    // Test Case 1: Valid Graph
    vector<int> d1 = {4, 3, 3, 2, 2};
    cout << "Test 1: " << (is_valid_simple_graph(d1) ? "Valid" : "Invalid") << endl;

    // Test Case 2: Invalid Graph
    vector<int> d2 = {3, 3, 3, 1};
    cout << "Test 2: " << (is_valid_simple_graph(d2) ? "Valid" : "Invalid") << endl;

    return 0;
}
