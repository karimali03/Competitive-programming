// Digit Trie [0-9] - CP template
// Store numbers as strings when leading zeros matter (phone numbers, IDs, etc.).

struct Trie {
    static const int ALPHA = 10;

    struct node {
        array<int, ALPHA> nxt;
        bool leaf;
        pair<int,int> cnt;
        int end_cnt;

        node() {
            nxt.fill(-1);
            leaf = false;
            cnt = {0,0};
            end_cnt = 0;
        }
    };

    vector<node> child;
    int words;
    int total_len;

    Trie() {
        child.push_back(node());
        words = 0;
        total_len = 0;
    }

    void reserve(int nodes) {
        child.reserve(nodes);
    }

    void clear() {
        child.clear();
        child.push_back(node());
        words = 0;
        total_len = 0;
    }

    int size() const {
        return words;
    }

    bool empty() const {
        return words == 0;
    }

    void insert(string &s) {
        int cur = 0;
        int sz = s.size();
        words++;
        total_len += sz;

        for(char c : s) {
            int idx = c - '0';
            if(child[cur].nxt[idx] == -1) {
                child[cur].nxt[idx] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[idx];
            child[cur].cnt.first++;
            child[cur].cnt.second += sz;
        }

        child[cur].end_cnt++;
        child[cur].leaf = true;
    }

    // Convenience wrapper for ordinary integers.
    // NOTE: to_string removes leading zeros.
    void insert_num(int num) {
        string s = to_string(num);
        insert(s);
    }

    int get_node(const string &s) const {
        int cur = 0;
        for(char c : s) {
            int idx = c - '0';
            int to = child[cur].nxt[idx];
            if(to == -1 || child[to].cnt.first == 0) return -1;
            cur = to;
        }
        return cur;
    }

    bool word_exist(const string &s) const {
        if(s.empty()) return child[0].end_cnt > 0;
        int cur = get_node(s);
        return cur != -1 && child[cur].leaf;
    }

    bool prefix_exist(const string &s) const {
        if(s.empty()) return !empty();
        return get_node(s) != -1;
    }

    int count_word(const string &s) const {
        if(s.empty()) return child[0].end_cnt;
        int cur = get_node(s);
        return cur == -1 ? 0 : child[cur].end_cnt;
    }

    int count_prefix(const string &s) const {
        if(s.empty()) return words;
        int cur = get_node(s);
        return cur == -1 ? 0 : child[cur].cnt.first;
    }

    pair<int,int> prefix_stats(const string &s) const {
        if(s.empty()) return {words, total_len};
        int cur = get_node(s);
        return cur == -1 ? pair<int,int>{0,0} : child[cur].cnt;
    }

    bool erase(const string &s) {
        if(!word_exist(s)) return false;

        int cur = 0;
        int sz = s.size();
        words--;
        total_len -= sz;

        for(char c : s) {
            int idx = c - '0';
            cur = child[cur].nxt[idx];
            child[cur].cnt.first--;
            child[cur].cnt.second -= sz;
        }

        child[cur].end_cnt--;
        child[cur].leaf = (child[cur].end_cnt > 0);
        return true;
    }

    // 0-indexed kth digit-string lexicographically, counting duplicates.
    // For equal-length decimal strings, lexicographic order == numeric order.
    string kth_word(int k) const {
        if(k < 0 || k >= words) return "";

        string ret;
        int cur = 0;

        while(true) {
            if(k < child[cur].end_cnt) return ret;
            k -= child[cur].end_cnt;

            bool moved = false;
            for(int i = 0; i < ALPHA; i++) {
                int to = child[cur].nxt[i];
                int sub = (to == -1 ? 0 : child[to].cnt.first);

                if(k < sub) {
                    ret += char('0' + i);
                    cur = to;
                    moved = true;
                    break;
                }
                k -= sub;
            }

            if(!moved) return "";
        }
    }

    // Number of stored digit-strings lexicographically smaller than s.
    int count_less(const string &s) const {
        int cur = 0;
        int res = 0;

        for(char c : s) {
            res += child[cur].end_cnt;

            int idx = c - '0';
            for(int i = 0; i < idx; i++) {
                int to = child[cur].nxt[i];
                if(to != -1) res += child[to].cnt.first;
            }

            int to = child[cur].nxt[idx];
            if(to == -1 || child[to].cnt.first == 0) return res;
            cur = to;
        }
        return res;
    }

    // Useful for phone-list / prefix-free problems.
    // Returns true if inserting s would conflict because:
    // - an existing string is a prefix of s,
    // - s is a prefix of an existing string,
    // - or s already exists.
    bool prefix_conflict(const string &s) const {
        int cur = 0;

        for(char c : s) {
            if(child[cur].end_cnt > 0) return true;

            int idx = c - '0';
            int to = child[cur].nxt[idx];
            if(to == -1 || child[to].cnt.first == 0) return false;
            cur = to;
        }

        if(child[cur].end_cnt > 0) return true; // duplicate

        for(int i = 0; i < ALPHA; i++) {
            int to = child[cur].nxt[i];
            if(to != -1 && child[to].cnt.first > 0) return true;
        }
        return false;
    }

    // Check whether the whole currently stored set is prefix-free.
    bool is_prefix_free() const {
        for(const node &nd : child) {
            if(nd.end_cnt > 1) return false;
            if(nd.end_cnt == 0) continue;

            for(int i = 0; i < ALPHA; i++) {
                int to = nd.nxt[i];
                if(to != -1 && child[to].cnt.first > 0) return false;
            }
        }
        return true;
    }
};

/*
=========================== CP NOTES ===========================

1) Store digit sequences as string when leading zeros matter:
       "00123" != "123"
   insert_num() is only for ordinary integers where leading zeros do not matter.

2) Classic digit-trie problems
   - phone list consistency / prefix-free sets
   - counting IDs/numbers with a given prefix
   - lexicographic kth digit sequence
   - dictionary of fixed-length decimal codes

3) Numeric order warning
   Lexicographic order is NOT normal numeric order for variable-length strings:
       "10" < "2" lexicographically, but 10 > 2 numerically.
   They coincide when all strings have equal length (with leading zeros if needed).

4) Prefix-free trick
   While inserting s:
   - if you meet an existing end -> old string is prefix of s
   - after consuming s, if an active child exists -> s is prefix of an old string
   - if end_cnt > 0 -> duplicate
   prefix_conflict() performs exactly this check without inserting.

5) Reserve
   At most one new trie node per inserted digit:
       trie.reserve(1 + total_digits);

6) cnt meaning is kept identical to your string trie:
   cnt.first  = number of strings passing through node
   cnt.second = sum of their full lengths

===============================================================
*/
