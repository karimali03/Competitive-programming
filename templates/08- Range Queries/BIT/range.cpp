// 1-indexed
// range update - point query
struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void add(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    long long sum(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    // add val to all a[l..r]
    void range_add(int l, int r, long long val) {
        add(l, val);
        if (r + 1 <= n)
            add(r + 1, -val);
    }

    // get a[i]
    long long point_query(int i) {
        return sum(i);
    }
};