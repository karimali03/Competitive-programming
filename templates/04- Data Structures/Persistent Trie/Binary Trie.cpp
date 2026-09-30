struct PersistentTrie {
    static const int LOG = 30;

    struct Node {
        int nxt[2];
        int cnt;

        Node() {
            nxt[0] = nxt[1] = 0;
            cnt = 0;
        }
    };

    vector<Node> tr;
    vector<int> root;

    PersistentTrie(int n = 0) {
        tr.reserve((n + 5) * (LOG + 2));

        // node 0 = null node
        tr.push_back(Node());

        // root[i] = trie containing first i inserted values
        root.assign(n + 1, 0);
    }

    // Copy a node from the previous version.
    int clone(int node) {
        tr.push_back(tr[node]);
        return (int)tr.size() - 1;
    }

    // Create a new version by inserting x into oldRoot.
    int insert(int oldRoot, int x) {
        int newRoot = clone(oldRoot);

        int oldNode = oldRoot;
        int newNode = newRoot;

        tr[newNode].cnt++;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            int oldChild = tr[oldNode].nxt[b];
            int newChild = clone(oldChild);

            tr[newNode].nxt[b] = newChild;

            oldNode = oldChild;
            newNode = newChild;

            tr[newNode].cnt++;
        }

        return newRoot;
    }

    // root[i] contains values added at positions [1..i].
    void add(int i, int x) {
        root[i] = insert(root[i - 1], x);
    }

    // Number of values from range-version [l..r]
    // that go through child 'b' of the current nodes.
    int count_branch(int leftRoot, int rightRoot, int b) {
        int L = tr[leftRoot].nxt[b];
        int R = tr[rightRoot].nxt[b];

        return tr[R].cnt - tr[L].cnt;
    }

    /*
        max(x ^ a[j]), l <= j <= r

        root[r]     contains a[1..r]
        root[l - 1] contains a[1..l-1]

        Their count difference represents exactly a[l..r].
    */
    int max_xor(int l, int r, int x) {
        int LRoot = root[l - 1];
        int RRoot = root[r];

        int ans = 0;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int want = b ^ 1;

            if (count_branch(LRoot, RRoot, want) > 0) {
                ans |= (1 << bit);

                LRoot = tr[LRoot].nxt[want];
                RRoot = tr[RRoot].nxt[want];
            }
            else {
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
            }
        }

        return ans;
    }

    /*
        min(x ^ a[j]), l <= j <= r
    */
    int min_xor(int l, int r, int x) {
        int LRoot = root[l - 1];
        int RRoot = root[r];

        int ans = 0;

        for (int bit = LOG; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            if (count_branch(LRoot, RRoot, b) > 0) {
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
            }
            else {
                ans |= (1 << bit);

                b ^= 1;
                LRoot = tr[LRoot].nxt[b];
                RRoot = tr[RRoot].nxt[b];
            }
        }

        return ans;
    }
};
