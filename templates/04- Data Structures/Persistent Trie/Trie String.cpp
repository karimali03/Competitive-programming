struct PersistentStringTrie {
    static const int ALPHA = 26;

    struct Node {
        int nxt[ALPHA];
        int cnt;       // strings passing through this node
        int endings;   // strings ending here

        Node() {
            memset(nxt, 0, sizeof(nxt));
            cnt = endings = 0;
        }
    };

    vector<Node> tr;
    vector<int> root;

    PersistentStringTrie(int n = 0) {
        tr.push_back(Node());          // node 0 = null
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
            int x = c - 'a';

            int oldChild = tr[oldNode].nxt[x];
            int newChild = clone(oldChild);

            tr[newNode].nxt[x] = newChild;

            oldNode = oldChild;
            newNode = newChild;

            tr[newNode].cnt++;
        }

        tr[newNode].endings++;

        return newRoot;
    }

    // root[i] contains strings inserted at positions [1..i]
    void add(int i, const string &s) {
        root[i] = insert(root[i - 1], s);
    }

    // Number of exact occurrences of s among strings [l..r]
    int count_word(int l, int r, const string &s) {
        int L = root[l - 1];
        int R = root[r];

        for (char c : s) {
            int x = c - 'a';

            L = tr[L].nxt[x];
            R = tr[R].nxt[x];

            if (tr[R].cnt - tr[L].cnt == 0)
                return 0;
        }

        return tr[R].endings - tr[L].endings;
    }

    // Number of strings in [l..r] having prefix s
    int count_prefix(int l, int r, const string &s) {
        int L = root[l - 1];
        int R = root[r];

        for (char c : s) {
            int x = c - 'a';

            L = tr[L].nxt[x];
            R = tr[R].nxt[x];

            if (tr[R].cnt - tr[L].cnt == 0)
                return 0;
        }

        return tr[R].cnt - tr[L].cnt;
    }
};
