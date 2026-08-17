struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    // a[i] += val
    void add(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    // sum [1..i]
    long long sum(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    // sum [l..r]
    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // smallest index i such that sum(i) >= k
    // BIT values must be non-negative
    int kth(long long k) {
        int pos = 0;

        for (int pw = 1 << __lg(n); pw; pw >>= 1) {
            int nxt = pos + pw;

            if (nxt <= n && bit[nxt] < k) {
                pos = nxt;
                k -= bit[nxt];
            }
        }

        return pos + 1;
    }
};