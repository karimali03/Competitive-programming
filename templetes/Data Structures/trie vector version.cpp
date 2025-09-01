
struct Trie {
    struct node {
        unordered_map<int,int>nxt;
        bool leaf;
        pair<int,int>cnt;
        node() {
            leaf = false;
            cnt = {0,0};
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(string &s) {
        int cur = 0;
        int sz = s.size();
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) {
                child[cur].nxt[idx] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[idx];
            child[cur].cnt.first++;
            child[cur].cnt.second+=sz;
        }
        child[cur].leaf = true;
    }
    bool word_exist(const string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) return false;
            cur = child[cur].nxt[idx];
        }
        return child[cur].leaf;
    }

    bool prefix_exist(const string &s) {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!child[cur].nxt.count(idx)) return false;
            cur = child[cur].nxt[idx];
        }
        return true;
    }
};
