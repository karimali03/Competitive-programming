struct operation {
    int type, v;
    operation(int type = 0, int v = 0) : type(type), v(v) {}
};

struct segment_tree {
private:
    int size;
    vector<operation> lazy;
    const int NO_OPERATION = LLONG_MAX;
    
    operation operation_lazy(operation a, operation b) {
        return (a.type == NO_OPERATION) ? b : (b.type == NO_OPERATION) ? a : operation{a.type, a.v + b.v};
    }
    
    void propagate(int idx, int lx, int rx) {
        if (rx - lx == 1) return;
        lazy[2 * idx + 1] = operation_lazy(lazy[2 * idx + 1], lazy[idx]);
        lazy[2 * idx + 2] = operation_lazy(lazy[2 * idx + 2], lazy[idx]);
        lazy[idx] = {NO_OPERATION};
    }
    
    void _add(int l, int r, int v, int idx, int lx, int rx) {
        propagate(idx, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            lazy[idx] = operation_lazy(lazy[idx], {1, v});
            return;
        }
        int m = (lx + rx) / 2;
        _add(l, r, v, idx * 2 + 1, lx, m);
        _add(l, r, v, idx * 2 + 2, m, rx);
    }
    
    int _get(int i, int idx, int lx, int rx) {
        propagate(idx, lx, rx);
        if (rx - lx == 1) return lazy[idx].v;
        int m = (lx + rx) / 2;
        return (i < m) ? _get(i, idx * 2 + 1, lx, m) : _get(i, idx * 2 + 2, m, rx);
    }

public:
    segment_tree(int n) : size(1) {
        while (size < n) size <<= 1;
        lazy = vector<operation>(size << 1, {NO_OPERATION});
    }

    void add(int l, int r, int v) {
        _add(l, r, v, 0, 0, size);
    }

    int get(int i) {
        return _get(i, 0, 0, size);
    }
};
