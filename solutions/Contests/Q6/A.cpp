#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

const int N = 200000 + 5;
const ull PR = 911382323ULL;
ull pw[N];

void init() {
    pw[0] = 1;
    for (int i = 1; i < N; ++i) {
        // Unsigned overflow is intentional: hashing modulo 2^64.
        pw[i] = pw[i - 1] * PR;
    }
}

struct item {
    // H[shift] = hash after applying this additional shift.
    ull H[26]{};
    int cnt = 0;
    int offset = 0;

    ull getsum(int extraShift = 0) const {
        int index = offset + extraShift;
        if (index >= 26) index -= 26;
        return H[index];
    }
};

struct query_item {
    ull hash = 0;
    int cnt = 0;

    ull getsum() const {
        return hash;
    }
};

class SegmentTree {
public:
    void set(int l, int r, int value) {
        set(0, 0, size - 1, l, r, value % 26);
    }

    query_item getrange(int l, int r) {
        return getrange(0, 0, size - 1, l, r);
    }

    void build(const string &s) {
        size = 1;
        while (size < (int)s.size()) size *= 2;

        tree.assign(2 * size, item());
        lazy.assign(2 * size, 0);
        build(s, 0, 0, size - 1);
    }

private:
    int size = 1;
    vector<item> tree;
    vector<unsigned char> lazy;

    ull combineHash(ull leftHash, ull rightHash, int leftLength) const {
        return leftHash + rightHash * pw[leftLength];
    }

    item merge(const item &left, const item &right) {
        item result;
        result.cnt = left.cnt + right.cnt;

        for (int shift = 0; shift < 26; ++shift) {
            result.H[shift] = combineHash(
                left.getsum(shift),
                right.getsum(shift),
                left.cnt
            );
        }

        // result.H[0] was built from the children's current states.
        result.offset = 0;
        return result;
    }

    query_item mergeQuery(const query_item &left,
                          const query_item &right) const {
        return {
            combineHash(left.hash, right.hash, left.cnt),
            left.cnt + right.cnt
        };
    }

    void apply(int node, int shift) {
        int newOffset = tree[node].offset + shift;
        if (newOffset >= 26) newOffset -= 26;
        tree[node].offset = newOffset;

        int newLazy = lazy[node] + shift;
        if (newLazy >= 26) newLazy -= 26;
        lazy[node] = static_cast<unsigned char>(newLazy);
    }

    void push(int node) {
        int shift = lazy[node];
        if (shift == 0) return;

        apply(2 * node + 1, shift);
        apply(2 * node + 2, shift);
        lazy[node] = 0;

        // Keep tree[node].offset. Its H array was not rebuilt here.
    }

    void set(int node, int lx, int rx,
             int l, int r, int value) {
        if (rx < l || r < lx) return;

        if (l <= lx && rx <= r) {
            apply(node, value);
            return;
        }

        push(node);
        int mid = (lx + rx) / 2;
        set(2 * node + 1, lx, mid, l, r, value);
        set(2 * node + 2, mid + 1, rx, l, r, value);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    query_item getrange(int node, int lx, int rx,
                        int l, int r) {
        if (rx < l || r < lx) return {};

        if (l <= lx && rx <= r) {
            return {tree[node].getsum(), tree[node].cnt};
        }

        push(node);
        int mid = (lx + rx) / 2;
        query_item left = getrange(2 * node + 1, lx, mid, l, r);
        query_item right = getrange(2 * node + 2, mid + 1, rx, l, r);
        return mergeQuery(left, right);
    }

    void build(const string &s, int node, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int)s.size()) {
                tree[node].cnt = 1;
                int letter = s[lx] - 'a';

                for (int shift = 0; shift < 26; ++shift) {
                    tree[node].H[shift] =
                        (letter + shift) % 26 + 1;
                }
            }
            return;
        }

        int mid = (lx + rx) / 2;
        build(s, 2 * node + 1, lx, mid);
        build(s, 2 * node + 2, mid + 1, rx);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    SegmentTree sg;
    sg.build(s);

    auto compare = [&](int l1, int l2, int len) {
        if (len == 0) return true;
        ull v1 = sg.getrange(l1, l1 + len - 1).getsum();
        ull v2 = sg.getrange(l2, l2 + len - 1).getsum();
        return v1 == v2;
    };

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            --r;
            sg.set(l, r, x);
            continue;
        }

        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        --l1;
        --r1;
        --l2;
        --r2;

        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int common = min(len1, len2);

        if (compare(l1, l2, common)) {
            if (len1 < len2) cout << "<\n";
            else if (len1 > len2) cout << ">\n";
            else cout << "=\n";
            continue;
        }

        // Find the first prefix length that is not equal.
        int l = 1, r = common;
        while (l < r) {
            int mid = (l + r) / 2;
            if (compare(l1, l2, mid)) l = mid + 1;
            else r = mid;
        }

        ull firstCharacter = sg.getrange(l1 + l - 1, l1 + l - 1).getsum();
        ull secondCharacter = sg.getrange(l2 + l - 1, l2 + l - 1).getsum();

        cout << (firstCharacter < secondCharacter ? '<' : '>') << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int testCases;
    cin >> testCases;
    while (testCases--) solve();

    return 0;
}