#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum size for N and Q
const int MAXN = 150005;

// The maximum value for k + N is around 300,000. 
// The next power of 2 is 2^19 = 524,288.
const int MAXM = 524300; 

// Fenwick trees for 0-bits and 1-bits
int bit0[MAXM];
int bit1[MAXM];

// Add value to Fenwick Tree (1-based indexing internally)
void add(int* tree, int i, int n, int delta) {
    for (++i; i <= n; i += i & -i) tree[i] += delta;
}

// Prefix sum from Fenwick Tree
int query(int* tree, int i) {
    int sum = 0;
    for (++i; i > 0; i -= i & -i) sum += tree[i];
    return sum;
}

// Range sum from Fenwick Tree
int query(int* tree, int l, int r) {
    if (l > r) return 0;
    return query(tree, r) - query(tree, l - 1);
}

struct Query {
    long long l, r, k;
};

struct Event {
    int id;
    int sign; // +1 for the right bound, -1 for the left bound
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<Query> queries(q);
    vector<vector<Event>> events(n + 1);

    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        // Break the query into two events for the prefix sum trick
        events[queries[i].l - 1].push_back({i, -1});
        events[queries[i].r].push_back({i, 1});
    }

    vector<long long> ans(q, 0);

    // Process each bit independently (from 0 up to 18)
    for (int p = 0; p <= 18; ++p) {
        long long M = 1LL << (p + 1); // Length of the full repeating cycle
        long long H = 1LL << p;       // Length of the half cycle (where bits are 1)

        // Clear the Fenwick trees up to size M
        for (int i = 0; i <= M; ++i) {
            bit0[i] = 0;
            bit1[i] = 0;
        }

        // Sweep line: walk through the array from left to right
        for (int i = 1; i <= n; ++i) {
            int rem = i % M;
            
            // Add the remainder to the respective bucket based on a[i]'s p-th bit
            if ((a[i] >> p) & 1) {
                add(bit1, rem, M, 1);
            } else {
                add(bit0, rem, M, 1);
            }

            // Process any queries that have a boundary at the current index
            for (const auto& ev : events[i]) {
                int q_id = ev.id;
                long long sign = ev.sign;
                long long l = queries[q_id].l;
                long long k = queries[q_id].k;

                // C groups the constants (k - l) for the formula
                long long C = (k - l) % M;
                if (C < 0) C += M; // Handle negative modulo in C++

                long long cnt0_ones = 0;
                long long cnt1_ones = 0;

                // Find the ranges [L, R] where the sequence bit is 1
                long long L1 = max(0LL, H - C);
                long long R1 = M - 1 - C;
                if (L1 <= R1) {
                    cnt0_ones += query(bit0, L1, R1);
                    cnt1_ones += query(bit1, L1, R1);
                }

                long long L2 = max(0LL, M + H - C);
                long long R2 = M - 1;
                if (L2 <= R2) {
                    cnt0_ones += query(bit0, L2, R2);
                    cnt1_ones += query(bit1, L2, R2);
                }

                // If a[i]'s bit is 1, it contributes to the final XOR sum when the sequence bit is 0.
                // Sequence bit 0 = Total insertions in bit1 MINUS insertions where sequence bit is 1.
                long long cnt1_total = query(bit1, 0, M - 1);
                long long cnt1_zeros = cnt1_total - cnt1_ones;

                // Total valid ones for bit p
                long long total_ones = cnt0_ones + cnt1_zeros;

                // Add to the query's total answer 
                // Multiply by (1 << p) because we are at the p-th bit position
                ans[q_id] += sign * total_ones * (1LL << p);
            }
        }
    }

    // Print the finalized answers for all queries
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}