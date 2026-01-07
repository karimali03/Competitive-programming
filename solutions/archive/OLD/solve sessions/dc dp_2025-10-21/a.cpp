#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

#define ln "\n"
#define ll long long

// A struct for the sparse table to answer Range Maximum Queries.
// It is optimized to return the index of the maximum element.
struct sparse {
    vector<vector<int>> mx;
    const vector<int>& org; // Use a reference to avoid copying the data
    int n;

    // Comparison function to find the index with the larger value
    bool is_better(int idx1, int idx2) {
        return org[idx1] > org[idx2];
    }

    sparse(const vector<int>& v) : org(v) {
        n = v.size();
        if (n == 0) return;
        int LOG = floor(log2(n)) + 1;
        mx.assign(n, vector<int>(LOG));

        for (int i = 0; i < n; i++) {
            mx[i][0] = i;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                int idx1 = mx[i][k - 1];
                int idx2 = mx[i + (1 << (k - 1))][k - 1];
                mx[i][k] = is_better(idx1, idx2) ? idx1 : idx2;
            }
        }
    }

    int query_max_index(int L, int R) {
        if (L > R) return -1; // Invalid range
        int k = floor(log2(R - L + 1));
        int idx1 = mx[L][k];
        int idx2 = mx[R - (1 << k) + 1][k];
        return is_better(idx1, idx2) ? idx1 : idx2;
    }
};


const int N = 5005;
ll pre[N][N]{};
// Function to apply updates to the 2D difference array (imos method)
// Adds `val` to the rectangle from (row l1, col r1) to (row l2, col r2)
void add(int l1, int r1, int l2, int r2, int val,int n) {
    if (l1 > l2 || r1 > r2) return;
    pre[l1][r1] += val;
    if (r2 + 1 < n) pre[l1][r2 + 1] -= val;
    if (l2 + 1 < n) pre[l2 + 1][r1] -= val;
    if (l2 + 1 < n && r2 + 1 < n) pre[l2 + 1][r2 + 1] += val;
}

void solve() {
    int n, m;
    cin >> n >> m;

    // A will store absolute coordinates
    vector<ll> A(n, 0);
    for (int i = 0; i < n - 1; i++) {
        ll dist;
        cin >> dist;
        A[i + 1] = A[i] + dist;
    }

    // Read deliciousness values
    vector<vector<int>> x(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> x[i][j];
        }
    }

    // Transpose the matrix so B[j] contains all deliciousness values for ticket j
    vector<vector<int>> B(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            B[j][i] = x[i][j];
        }
    }

    // Create a sparse table for each ticket
    vector<sparse> st;
    st.reserve(m);
    for (int i = 0; i < m; i++) {
        st.emplace_back(B[i]);
    }

    // The recursive Divide and Conquer function
    function<void(int, int, int)> dc =
        [&](int l, int r, int ticket_idx) {
        if (l > r) return;
        int opt_idx = st[ticket_idx].query_max_index(l, r);
        int value = B[ticket_idx][opt_idx];
        
        // Add `value` to the rectangle where `opt_idx` is the best choice
        // This is for all trips (i, j) where l <= i <= opt_idx <= j <= r
        add(l, opt_idx, opt_idx, r, value, n);
        
        dc(l, opt_idx - 1, ticket_idx);
        dc(opt_idx + 1, r, ticket_idx);
    };

    // Run the D&C for each ticket
    for (int i = 0; i < m; i++) {
        dc(0, n - 1, i);
    }

    // Reconstruct the final deliciousness grid from the difference array
    // First pass: prefix sums over columns
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            pre[i][j] += pre[i][j - 1];
        }
    }
    // Second pass: prefix sums over rows
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < n; i++) {
            pre[i][j] += pre[i - 1][j];
        }
    }

    // Find the final answer by checking every possible trip (i, j)
    ll max_happiness = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll deliciousness = pre[i][j];
            ll travel_cost = A[j] - A[i];
            max_happiness = max(max_happiness, deliciousness - travel_cost);
        }
    }

    cout << max_happiness << ln;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
