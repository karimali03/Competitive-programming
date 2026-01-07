#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ln "\n"

struct DSU {
    vector<int> parent, size, parity;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        parity.assign(n + 1, 0);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int get(int x) {
        if (x == parent[x]) return x;
        int root = get(parent[x]);
        if(root != parent[x])
        parity[x] = (parity[x] + parity[parent[x]]) ;
        parent[x] = root;
        return root;
    }

    bool merge(int x, int y) {
        int rx = get(x), ry = get(y);
        if (rx == ry) {
            // Check if they are in the same set with the same parity (i.e., odd cycle)
            return (parity[x] + parity[y]) % 2 == 1;
        }
        // Merge x's root into y's root, update parity
        parent[rx] = ry;
        parity[rx] = (1 + parity[x] + parity[y]);
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (!dsu.merge(a, b)) {
            cout << i + 1 << ln;
            return;
        }
    }
    cout << -1 << ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
