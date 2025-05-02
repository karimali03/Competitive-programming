#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define ln '\n'

void solve(int test_case) {
    int n, m;
    cin >> n >> m;
    vi v(n * m);

    // Read directions and build the permutation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            string s;
            cin >> s;
            int ii = i, jj = j;
            for (char ch : s) {
                if (ch == 'N') ii--;
                else if (ch == 'S') ii++;
                else if (ch == 'E') jj++;
                else if (ch == 'W') jj--;
            }
            v[i * m + j] = ii * m + jj;
        }
    }

    // Binary lifting table: sparse[i][j] = position after 2^i moves from j
    vector<vi> sparse(31, vi(n * m));
    sparse[0] = v;
    for (int i = 1; i < 31; ++i) {
        for (int j = 0; j < n * m; ++j) {
            sparse[i][j] = sparse[i - 1][sparse[i - 1][j]];
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y, k;
        cin >> x >> y >> k;
        x--, y--;
        int cur = x * m + y;

        for (int i = 0; i < 31; ++i) {
            if ((k >> i) & 1) {
                cur = sparse[i][cur];
            }
        }

        int final_i = cur / m + 1;
        int final_j = cur % m + 1;
        cout << final_i << " " << final_j << ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}
