struct PersistentDecimalTrie {
    static const int DIGITS = 10;

    struct Node {
        int nxt[DIGITS];
        int cnt;
        int endings;

        Node() {
            memset(nxt, 0, sizeof(nxt));
            cnt = endings = 0;
        }
    };

    vector<Node> tr;
    vector<int> root;

    PersistentDecimalTrie(int n = 0) {
        tr.push_back(Node());
        root.assign(n + 1, 0);
    }

    int clone(int node) {
        tr.push_back(tr[node]);
        return (int)tr.size() - 1;
    }

    int insert(int oldRoot, const string &s) {
        int newRoot = clone(oldRoot);

        int oldNode = oldRoot;
        int newNode = newRoot;

        tr[newNode].cnt++;

        for (char c : s) {
            int d = c - '0';

            int oldChild = tr[oldNode].nxt[d];
            int newChild = clone(oldChild);

            tr[newNode].nxt[d] = newChild;

            oldNode = oldChild;
            newNode = newChild;

            tr[newNode].cnt++;
        }

        tr[newNode].endings++;

        return newRoot;
    }

    void add(int i, const string &s) {
        root[i] = insert(root[i - 1], s);
    }

    // exact decimal string count in [l,r]
    int count_number(int l, int r, const string &s) {
        int L = root[l - 1];
        int R = root[r];

        for (char c : s) {
            int d = c - '0';

            L = tr[L].nxt[d];
            R = tr[R].nxt[d];

            if (tr[R].cnt - tr[L].cnt == 0)
                return 0;
        }

        return tr[R].endings - tr[L].endings;
    }

    // count numbers whose decimal representation starts with prefix s
    int count_prefix(int l, int r, const string &s) {
        int L = root[l - 1];
        int R = root[r];

        for (char c : s) {
            int d = c - '0';

            L = tr[L].nxt[d];
            R = tr[R].nxt[d];

            if (tr[R].cnt - tr[L].cnt == 0)
                return 0;
        }

        return tr[R].cnt - tr[L].cnt;
    }
};
