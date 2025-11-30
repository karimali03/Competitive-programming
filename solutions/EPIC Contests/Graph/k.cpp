#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define int long long

// Global variables
int n, m;
vector<string> g;
int pref[305][305];
int vis[305][305][2];
int vid = 0;

// O(1) Check sum of obstacles in rectangle
int get_sum(int r1, int c1, int r2, int c2) {
    if (r1 > r2) swap(r1, r2);
    if (c1 > c2) swap(c1, c2);
    r1 = max(0LL, r1); c1 = max(0LL, c1);
    r2 = min(n - 1, r2); c2 = min(m - 1, c2);
    if (r1 > r2 || c1 > c2) return 0;
    
    return pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1] - pref[r2 + 1][c1] + pref[r1][c1];
}

// Check if a table at specific position is valid (Static check)
bool is_valid_pos(int r, int c, int k, int type) {
    if (type == 0) { // Horizontal
        if (c < 0 || c + k > m || r < 0 || r >= n) return false;
        return get_sum(r, c, r, c + k - 1) == 0;
    } else { // Vertical
        if (r < 0 || r + k > n || c < 0 || c >= m) return false;
        return get_sum(r, c, r + k - 1, c) == 0;
    }
}

// Check if Rotation is valid
// pivot_r, pivot_c: Coordinates of the pivot
// r_step, c_step: Direction of the sweep (1 or -1) representing the quadrant
// k: length of table
bool can_rotate(int pivot_r, int pivot_c, int r_step, int c_step, int k) {
    // We need to check all cells (i, j) relative to pivot such that i^2 + j^2 <= (k-1)^2
    // We iterate over the row offset 'i'
    for (int i = 1; i < k; ++i) {
        // Calculate max column offset 'j' for this 'i'
        // i^2 + j^2 <= (k-1)^2  => j <= sqrt((k-1)^2 - i^2)
        int max_dist_sq = (k - 1) * (k - 1);
        int rem = max_dist_sq - i * i;
        if (rem < 0) break;
        int j = floor(sqrt(rem));
        
        if (j == 0) continue; 
        
        // Define the row in absolute coordinates
        int r = pivot_r + i * r_step;
        
        // Define the column range in absolute coordinates
        // From pivot_c + 1*c_step to pivot_c + j*c_step
        int c_start = pivot_c + 1 * c_step;
        int c_end = pivot_c + j * c_step;
        
        if (get_sum(r, c_start, r, c_end) > 0) return false;
    }
    return true;
}

bool check(int k) {
    if (k == 0) return false; // Should not happen based on binary search range
    vid++;
    
    // Queue stores {r, c, dir}
    // dir: 0 = Horizontal, 1 = Vertical
    queue<array<int, 3>> q;

    // Initialize with all valid Horizontal entries in column 0
    for (int r = 0; r < n; ++r) {
        if (is_valid_pos(r, 0, k, 0)) {
            vis[r][0][0] = vid;
            q.push({r, 0, 0});
        }
    }

    while (!q.empty()) {
        auto [r, c, type] = q.front();
        q.pop();

        // Target: Horizontal table touching the last column
        if (type == 0 && c == m - k) return true;

        // 1. Slide Moves
        if (type == 0) { // Horizontal Slide
            int dc[] = {1, -1};
            for (int x : dc) {
                int nc = c + x;
                if (is_valid_pos(r, nc, k, 0) && vis[r][nc][0] != vid) {
                    vis[r][nc][0] = vid;
                    q.push({r, nc, 0});
                }
            }
        } else { // Vertical Slide
            int dr[] = {1, -1};
            for (int x : dr) {
                int nr = r + x;
                if (is_valid_pos(nr, c, k, 1) && vis[nr][c][1] != vid) {
                    vis[nr][c][1] = vid;
                    q.push({nr, c, 1});
                }
            }
        }

        // 2. Rotate Moves
        if (type == 0) { // Horizontal -> Vertical
            // Pivot Left (r, c) -> Ends up Vertical at (r, c) (Down) or (r-k+1, c) (Up)
            
            // Case A: Pivot Left (r, c), rotate Down
            // Target: Vertical at (r, c). Quadrant: Bottom-Right relative to (r,c) is swept?
            // Actually, H is Right of (r,c), V is Down of (r,c). Sweep is in Bottom-Right.
            if (is_valid_pos(r, c, k, 1)) {
                if (can_rotate(r, c, 1, 1, k)) {
                    if (vis[r][c][1] != vid) {
                        vis[r][c][1] = vid;
                        q.push({r, c, 1});
                    }
                }
            }
            
            // Case B: Pivot Left (r, c), rotate Up
            // Target: Vertical at (r - k + 1, c). H is Right, V is Up. Sweep Top-Right.
            if (is_valid_pos(r - k + 1, c, k, 1)) {
                if (can_rotate(r, c, -1, 1, k)) {
                    if (vis[r - k + 1][c][1] != vid) {
                        vis[r - k + 1][c][1] = vid;
                        q.push({r - k + 1, c, 1});
                    }
                }
            }
            
            // Case C: Pivot Right (r, c + k - 1), rotate Down
            // Target: Vertical at (r, c + k - 1). H is Left, V is Down. Sweep Bottom-Left.
            if (is_valid_pos(r, c + k - 1, k, 1)) {
                 if (can_rotate(r, c + k - 1, 1, -1, k)) {
                    if (vis[r][c + k - 1][1] != vid) {
                        vis[r][c + k - 1][1] = vid;
                        q.push({r, c + k - 1, 1});
                    }
                }
            }

            // Case D: Pivot Right (r, c + k - 1), rotate Up
            // Target: Vertical at (r - k + 1, c + k - 1). H is Left, V is Up. Sweep Top-Left.
            if (is_valid_pos(r - k + 1, c + k - 1, k, 1)) {
                if (can_rotate(r, c + k - 1, -1, -1, k)) {
                     if (vis[r - k + 1][c + k - 1][1] != vid) {
                        vis[r - k + 1][c + k - 1][1] = vid;
                        q.push({r - k + 1, c + k - 1, 1});
                    }
                }
            }
            
        } else { // Vertical -> Horizontal
            // Pivot Top (r, c)
            
            // Case A: Pivot Top, rotate Right -> H at (r, c)
            // V is Down, H is Right. Sweep Bottom-Right.
             if (is_valid_pos(r, c, k, 0)) {
                if (can_rotate(r, c, 1, 1, k)) {
                    if (vis[r][c][0] != vid) {
                        vis[r][c][0] = vid;
                        q.push({r, c, 0});
                    }
                }
            }

            // Case B: Pivot Top, rotate Left -> H at (r, c - k + 1)
            // V is Down, H is Left. Sweep Bottom-Left.
             if (is_valid_pos(r, c - k + 1, k, 0)) {
                if (can_rotate(r, c, 1, -1, k)) {
                    if (vis[r][c - k + 1][0] != vid) {
                        vis[r][c - k + 1][0] = vid;
                        q.push({r, c - k + 1, 0});
                    }
                }
            }
            
            // Pivot Bottom (r + k - 1, c)
            
            // Case C: Pivot Bottom, rotate Right -> H at (r + k - 1, c)
            // V is Up (relative to pivot), H is Right. Sweep Top-Right.
             if (is_valid_pos(r + k - 1, c, k, 0)) {
                if (can_rotate(r + k - 1, c, -1, 1, k)) {
                    if (vis[r + k - 1][c][0] != vid) {
                        vis[r + k - 1][c][0] = vid;
                        q.push({r + k - 1, c, 0});
                    }
                }
            }

            // Case D: Pivot Bottom, rotate Left -> H at (r + k - 1, c - k + 1)
            // V is Up, H is Left. Sweep Top-Left.
             if (is_valid_pos(r + k - 1, c - k + 1, k, 0)) {
                if (can_rotate(r + k - 1, c, -1, -1, k)) {
                    if (vis[r + k - 1][c - k + 1][0] != vid) {
                        vis[r + k - 1][c - k + 1][0] = vid;
                        q.push({r + k - 1, c - k + 1, 0});
                    }
                }
            }
        }
    }
    return false;
}

void solve(int test_case) {
    cin >> n >> m;
    g.resize(n);
    for(int i=0 ; i <n ; i++) cin>>g[i];

    // Reset Prefix Sum
    for(int i=0; i<=n; ++i) for(int j=0; j<=m; ++j) pref[i][j] = 0;

    // Build Prefix Sum
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + (g[i][j] == '#');
        }
    }

    // Binary Search for k
    int l = 1, r = min(n, m), ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t; 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}