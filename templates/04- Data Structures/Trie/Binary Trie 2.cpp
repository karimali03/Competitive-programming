// Binary Trie - CP template
// Keeps the original variable names / core logic, with safe active-node handling
// and extra common XOR-trie tricks.
//
// Assumptions:
// - Values are non-negative.
// - Bits used are [MAX_BITS ... 0]. MAX_BITS = 30 supports values <= 2^31 - 1.
// - rm(num) assumes num currently exists. Use erase(num) if you want a safe remove.
// - mex(xor_val) should be used with SET semantics (insert each distinct value once),
//   because subtree fullness is checked using cnt == capacity.

struct Trie {
    static const int MAX_BITS = 30;

    struct Node {
        int nxt[2];
        int cnt;
        bool leaf;

        Node() {
            nxt[0] = nxt[1] = -1;
            cnt = 0;
            leaf = false;
        }
    };

    vector<Node> nodes;

    // n = expected number of inserted values.
    Trie(int n = 0) {
        nodes.reserve(1 + n * (MAX_BITS + 1));
        nodes.push_back(Node());
    }

    void clear() {
        nodes.clear();
        nodes.push_back(Node());
    }

    int size() const {
        return nodes[0].cnt;
    }

    bool empty() const {
        return size() == 0;
    }

    // Returns true if this edge has at least one active value.
    bool has(int cur, int bit) const {
        int to = nodes[cur].nxt[bit];
        return to != -1 && nodes[to].cnt > 0;
    }

    void insert(int value) {
        int cur = 0;
        nodes[cur].cnt++;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            if (nodes[cur].nxt[b] == -1) {
                nodes[cur].nxt[b] = nodes.size();
                nodes.push_back(Node());
            }

            cur = nodes[cur].nxt[b];
            nodes[cur].cnt++;
        }

        nodes[cur].leaf = true;
    }

    // Assumes value exists.
    void remove(int value) {
        int cur = 0;
        nodes[cur].cnt--;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            cur = nodes[cur].nxt[b];
            nodes[cur].cnt--;
        }

        nodes[cur].leaf = (nodes[cur].cnt > 0);
    }

    // Number of active copies of value.
    int count(int value) const {
        int cur = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            if (nodes[cur].nxt[b] == -1)
                return 0;

            cur = nodes[cur].nxt[b];
        }

        return nodes[cur].cnt;
    }

    bool search(int value) const {
        return count(value) > 0;
    }

    // Safe remove.
    bool erase(int value) {
        if (!search(value))
            return false;

        remove(value);
        return true;
    }

    /*
        MEX after XORing every stored value with xor_value.

        IMPORTANT:
        Full-subtree checking using cnt is correct only if
        inserted values are distinct.
    */
    int mex(int xor_value) const {
        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0 && cur != -1; bit--) {
            int b = (xor_value >> bit) & 1;

            int preferred = nodes[cur].nxt[b];

            long long subtree_capacity = (1LL << bit);

            bool full =
                preferred != -1 &&
                nodes[preferred].cnt == subtree_capacity;

            if (full) {
                result |= (1LL << bit);
                cur = nodes[cur].nxt[b ^ 1];
            } else {
                cur = preferred;
            }
        }

        return result;
    }

    // Maximum value of (value ^ stored_value).
    int max_xor(int value) const {
        if (empty())
            return 0;

        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            if (has(cur, b ^ 1)) {
                result |= (1LL << bit);
                cur = nodes[cur].nxt[b ^ 1];
            } else if (has(cur, b)) {
                cur = nodes[cur].nxt[b];
            } else {
                break;
            }
        }

        return result;
    }

    // Minimum value of (value ^ stored_value).
    int min_xor(int value) const {
        if (empty())
            return 0;

        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            if (has(cur, b)) {
                cur = nodes[cur].nxt[b];
            } else if (has(cur, b ^ 1)) {
                result |= (1LL << bit);
                cur = nodes[cur].nxt[b ^ 1];
            } else {
                break;
            }
        }

        return result;
    }

    // Stored value x that maximizes (value ^ x).
    int max_xor_element(int value) const {
        return value ^ max_xor(value);
    }

    // Stored value x that minimizes (value ^ x).
    int min_xor_element(int value) const {
        return value ^ min_xor(value);
    }

    /*
        Counts active stored values v such that:

            (value ^ v) < limit
    */
    int count_xor_less_than(int value, long long limit) const {
        if (limit <= 0 || empty())
            return 0;

        const long long MAX_XOR_VALUE = (1LL << (MAX_BITS + 1));

        if (limit >= MAX_XOR_VALUE)
            return size();

        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            if (cur == -1)
                break;

            int value_bit = (value >> bit) & 1;
            int limit_bit = (limit >> bit) & 1;

            if (limit_bit == 1) {
                /*
                    XOR bit = 0

                    Since limit bit = 1, choosing XOR bit 0
                    makes the number strictly smaller immediately.

                    stored_bit = value_bit
                */
                int smaller_branch = nodes[cur].nxt[value_bit];

                if (smaller_branch != -1)
                    result += nodes[smaller_branch].cnt;

                /*
                    Continue while still equal to limit:

                    XOR bit = 1
                    stored_bit = value_bit ^ 1
                */
                cur = nodes[cur].nxt[value_bit ^ 1];
            } else {
                /*
                    limit bit = 0

                    XOR bit must also be 0,
                    otherwise XOR becomes greater than limit.

                    stored_bit = value_bit
                */
                cur = nodes[cur].nxt[value_bit];
            }
        }

        return result;
    }

    /*
        Counts active stored values v such that:

            (value ^ v) <= limit
    */
    int count_xor_leq(int value, long long limit) const {
        return count_xor_less_than(value, limit + 1);
    }

    /*
        Counts active stored values v such that:

            left <= (value ^ v) <= right
    */
    int count_xor_range(
        int value,
        long long left,
        long long right
    ) const {
        if (left > right)
            return 0;

        return count_xor_less_than(value, right + 1)
             - count_xor_less_than(value, left);
    }

    /*
        Returns the k-th smallest value of:

            value ^ stored_value

        k is 0-indexed.
        Duplicates are counted.

        Returns -1 if k is invalid.
    */
    int kth_xor(int value, int k) const {
        if (k < 0 || k >= size())
            return -1;

        int cur = 0;
        int result = 0;

        for (int bit = MAX_BITS; bit >= 0; bit--) {
            int b = (value >> bit) & 1;

            /*
                To make XOR bit 0:
                stored_bit must equal value_bit.
            */
            int zero_branch = nodes[cur].nxt[b];

            int zero_count =
                zero_branch == -1
                ? 0
                : nodes[zero_branch].cnt;

            if (k < zero_count) {
                // kth value is in XOR-bit-0 branch.
                cur = zero_branch;
            } else {
                // Skip all XOR-bit-0 values.
                k -= zero_count;

                result |= (1LL << bit);

                cur = nodes[cur].nxt[b ^ 1];
            }
        }

        return result;
    }
};


/*
=========================== CP NOTES ===========================

1) Node count / memory
   Each inserted value creates at most MAX_BITS + 1 new nodes.
   If q inserts are known:
       trie.reserve(1 + q * (Trie::MAX_BITS + 1));

2) MAX_BITS
   - values < 2^31  -> MAX_BITS = 30
   - values < 2^20  -> MAX_BITS = 19
   - for long long up to about 1e18, use MAX_BITS = 60 and long long values.

3) max/min XOR
   At each bit:
   - max XOR: prefer the opposite bit.
   - min XOR: prefer the same bit.

4) XOR inequality
   calc(x, y) counts:
       (x ^ a) < y
   This is a bit-DP / trie walk: whenever y has bit 1, taking XOR-bit 0
   makes the prefix strictly smaller, so the whole matching subtree can be added.

5) kth XOR
   The branch producing XOR-bit 0 comes first lexicographically/numerically.
   Its subtree cnt tells whether the kth answer is there.

6) Deletion
   rm() only decreases cnt; it does NOT physically delete nodes.
   Therefore queries must use cnt > 0 to distinguish active branches from stale nodes.

7) mex(xor_val)
   Classic "MEX under global XOR" trick.
   A subtree is full iff cnt == number of possible values inside it.
   This requires SET semantics: duplicates make cnt larger without filling new values.

8) Useful identity
   If best_xor = num ^ x, then:
       x = num ^ best_xor
   so find_max_xor_element() / find_min_xor_element() need no second traversal.

9) Empty trie
   max/min XOR queries are normally called only when size() > 0.
   kth_xor() explicitly guards invalid k.

===============================================================
*/
