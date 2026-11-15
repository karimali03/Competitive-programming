struct RollbackDSU {
    vector<int> par, sz, dif;
    vector<array<int, 2>> cnt;

    int cc, totalMin = 0;
    int bad = 0;

    struct Change {
        int rx, ry, cost, oldMin;
        bool conflict;
    };

    vector<Change> history;

    RollbackDSU(int n)
        : par(n), sz(n, 1), dif(n, 0),
          cnt(n, {1, 0}), cc(n) {
        iota(par.begin(), par.end(), 0);
    }

    // Returns {root, parity from x to root}
    // NO path compression (required for rollback)
    pair<int, int> get(int x) const {
        int d = 0;

        while (x != par[x]) {
            d ^= dif[x];
            x = par[x];
        }

        return {x, d};
    }

    // w = 0: same side
    // w = 1: different sides
    // Returns false if THIS constraint is contradictory
    bool merge(int x, int y, int w = 0) {
        auto [rx, dx] = get(x);
        auto [ry, dy] = get(y);

        if (rx == ry) {
            bool conflict = ((dx ^ dy) != w);

            history.push_back({
                -1, -1, 0, totalMin, conflict
            });

            if (conflict) bad++;

            return !conflict;
        }

        int cost = dx ^ dy ^ w;

        if (sz[rx] < sz[ry]) {
            swap(rx, ry);
        }

        history.push_back({
            rx, ry, cost, totalMin, false
        });

        totalMin -= min(cnt[rx][0], cnt[rx][1]);
        totalMin -= min(cnt[ry][0], cnt[ry][1]);

        par[ry] = rx;
        dif[ry] = cost;

        sz[rx] += sz[ry];

        cnt[rx][0] += cnt[ry][cost];
        cnt[rx][1] += cnt[ry][cost ^ 1];

        totalMin += min(cnt[rx][0], cnt[rx][1]);

        cc--;

        return true;
    }

    // Undo the most recent merge operation
    void undo() {
        if (history.empty()) return;

        auto [rx, ry, cost, oldMin, conflict] = history.back();
        history.pop_back();

        if (rx == -1) {
            if (conflict) bad--;
            return;
        }

        par[ry] = ry;
        dif[ry] = 0;

        sz[rx] -= sz[ry];

        cnt[rx][0] -= cnt[ry][cost];
        cnt[rx][1] -= cnt[ry][cost ^ 1];

        totalMin = oldMin;
        cc++;
    }

    // Save current state
    int snapshot() const {
        return (int)history.size();
    }

    // Restore a saved state
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            undo();
        }
    }

    // Component size
    int size(int x) const {
        return sz[get(x).first];
    }

    // Side sizes
    array<int, 2> sides(int x) const {
        return cnt[get(x).first];
    }

    int minSide(int x) const {
        auto [r, d] = get(x);
        return min(cnt[r][0], cnt[r][1]);
    }

    int maxSide(int x) const {
        auto [r, d] = get(x);
        return max(cnt[r][0], cnt[r][1]);
    }

    // Are all active parity constraints satisfiable?
    bool consistent() const {
        return bad == 0;
    }

    // If connected, returns parity between x and y
    // Otherwise returns -1
    int relation(int x, int y) const {
        auto [rx, dx] = get(x);
        auto [ry, dy] = get(y);

        if (rx != ry) return -1;

        return dx ^ dy;
    }
};
