struct DSU {
    vector<int> sz, par, dif;
    vector<array<int, 2>> cnt;
    int cc, totalMin = 0;

    DSU(int n) : sz(n, 1), par(n), dif(n, 0),
                 cnt(n, {1, 0}), cc(n) {
        iota(par.begin(), par.end(), 0);
    }

    int get(int x) {
        if (x == par[x]) return x;

        int root = get(par[x]);

        dif[x] ^= dif[par[x]];

        return par[x] = root;
    }

    // w = 0: x and y belong to the same side
    // w = 1: x and y belong to different sides
    // Returns false if a contradiction is found
    bool merge(int x, int y, int w = 0) {
        int rx = get(x), ry = get(y);

        if (rx == ry) {
            return ((dif[x] ^ dif[y]) == w);
        }

        int cost = dif[x] ^ dif[y] ^ w;

        // Remove old contributions
        totalMin -= min(cnt[rx][0], cnt[rx][1]);
        totalMin -= min(cnt[ry][0], cnt[ry][1]);

        if (sz[rx] < sz[ry]) {
            swap(rx, ry);
        }

        par[ry] = rx;
        dif[ry] = cost;

        sz[rx] += sz[ry];

        // Merge side counts
        cnt[rx][0] += cnt[ry][cost];
        cnt[rx][1] += cnt[ry][cost ^ 1];

        // Add new contribution
        totalMin += min(cnt[rx][0], cnt[rx][1]);

        cc--;
        return true;
    }

    // Returns sizes of both sides
    array<int, 2> sides(int x) {
        return cnt[get(x)];
    }

    // Minimum side size in x's component
    int minSide(int x) {
        int r = get(x);
        return min(cnt[r][0], cnt[r][1]);
    }

    // Maximum side size in x's component
    int maxSide(int x) {
        int r = get(x);
        return max(cnt[r][0], cnt[r][1]);
    }
};
