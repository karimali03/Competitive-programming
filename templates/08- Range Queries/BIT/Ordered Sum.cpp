struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n = 0) : n(n), bit(n + 1) {}

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

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // first index with prefix sum >= k
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


struct OrderedSum {
    int n;
    BIT cnt, sum;
    vector<long long> val; // val[i] = actual value of compressed index i

    OrderedSum(vector<long long> values)
        : n(values.size()), cnt(n), sum(n), val(n + 1) {

        for (int i = 1; i <= n; i++)
            val[i] = values[i - 1];
    }

    // add/remove occurrence at compressed index i
    // delta = +1 insert, -1 erase
    void add(int i, int delta) {
        cnt.add(i, delta);
        sum.add(i, val[i] * delta);
    }

    // number of existing elements
    long long size() {
        return cnt.sum(n);
    }

    // sum of smallest k existing elements
    long long first_k_sum(long long k) {
        if (k <= 0) return 0;

        int i = cnt.kth(k);

        long long beforeCnt = cnt.sum(i - 1);
        long long beforeSum = sum.sum(i - 1);

        long long need = k - beforeCnt;

        return beforeSum + need * val[i];
    }
};