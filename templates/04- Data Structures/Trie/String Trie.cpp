// Lowercase String Trie - CP template
// Same variable names / original cnt meaning, optimized for the known alphabet [a-z].
//
// cnt.first  = number of inserted strings passing through this node.
// cnt.second = sum of FULL lengths of those strings (preserved from your template).
// end_cnt    = multiplicity of the exact word ending here.

struct Trie {
    static const int ALPHA = 26;

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

    // Optional speed optimization when total inserted characters are known.
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

        for (char c : s) {
            int idx = c - 'a';
            if (child[cur].nxt[idx] == -1) {
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

    // Returns the trie node of s, or -1 if no ACTIVE string has this prefix.
    int get_node(const string &s) const {
        int cur = 0;
        for (char c : s) {
            int idx = c - 'a';
            int to = child[cur].nxt[idx];
            if (to == -1 || child[to].cnt.first == 0) return -1;
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

    // Number of inserted strings equal to s.
    int count_word(const string &s) const {
        if(s.empty()) return child[0].end_cnt;
        int cur = get_node(s);
        return cur == -1 ? 0 : child[cur].end_cnt;
    }

    // Number of inserted strings starting with s.
    int count_prefix(const string &s) const {
        if(s.empty()) return words;
        int cur = get_node(s);
        return cur == -1 ? 0 : child[cur].cnt.first;
    }

    // Preserves your original pair statistic for a prefix.
    // {count of strings with prefix, sum of their full lengths}
    pair<int,int> prefix_stats(const string &s) const {
        if(s.empty()) return {words, total_len};
        int cur = get_node(s);
        return cur == -1 ? pair<int,int>{0,0} : child[cur].cnt;
    }

    // Safe erase of ONE copy. Nodes stay allocated, counts become inactive.
    bool erase(const string &s) {
        if(!word_exist(s)) return false;

        int cur = 0;
        int sz = s.size();
        words--;
        total_len -= sz;

        for(char c : s) {
            int idx = c - 'a';
            cur = child[cur].nxt[idx];
            child[cur].cnt.first--;
            child[cur].cnt.second -= sz;
        }

        child[cur].end_cnt--;
        child[cur].leaf = (child[cur].end_cnt > 0);
        return true;
    }

    // Lexicographically smallest common prefix of ALL inserted strings.
    string lcp_all() const {
        if(empty() || child[0].end_cnt > 0) return "";

        string ret;
        int cur = 0;

        while(true) {
            if(child[cur].end_cnt > 0) break;

            int nxt_cur = -1;
            int idx = -1;
            int active = 0;

            for(int i = 0; i < ALPHA; i++) {
                int to = child[cur].nxt[i];
                if(to != -1 && child[to].cnt.first > 0) {
                    active++;
                    nxt_cur = to;
                    idx = i;
                }
            }

            if(active != 1) break;
            ret += char('a' + idx);
            cur = nxt_cur;
        }
        return ret;
    }

    // 0-indexed kth string in lexicographic order, counting duplicates.
    // Returns "" for invalid k (so if empty strings are valid in your problem,
    // check k before calling / adapt the sentinel).
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
                    ret += char('a' + i);
                    cur = to;
                    moved = true;
                    break;
                }
                k -= sub;
            }

            if(!moved) return ""; // should not happen for valid k
        }
    }

    // Number of inserted strings strictly lexicographically smaller than s.
    int count_less(const string &s) const {
        int cur = 0;
        int res = 0;

        for(char c : s) {
            // A word ending at the current prefix is shorter, hence smaller.
            res += child[cur].end_cnt;

            int idx = c - 'a';
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
};

/*
=========================== CP NOTES ===========================

1) Why array<int,26> instead of unordered_map<int,int>?
   Your idx is always c - 'a', so the alphabet is fixed and tiny.
   array<int,26> is usually much faster, deterministic, and lower-overhead in CP.
   Use unordered_map/map only when the alphabet is genuinely large or sparse.

2) Complexity
   insert / erase / word_exist / prefix_exist / count_prefix:
       O(|s|)
   count_less:
       O(26 * |s|) = O(|s|) for lowercase English.
   Memory:
       O(total number of created trie nodes * 26)

3) Reserve trick
   Number of trie nodes <= 1 + total characters inserted.
       trie.reserve(1 + total_chars);
   This avoids repeated vector reallocations.

4) Duplicates
   leaf is only boolean, so end_cnt is added to support duplicates correctly.
   Example: insert("abc") twice -> count_word("abc") == 2.

5) Lazy deletion
   erase() does not free nodes; it decrements counts.
   get_node() checks cnt.first > 0 so stale paths are ignored.

6) Prefix counts
   count_prefix(p) is a classic trick for:
   - number of dictionary words with prefix p
   - autocomplete frequencies
   - prefix constraints / online queries

7) Lexicographic kth
   At a node:
   - exact words ending here come first
   - then child 'a', child 'b', ...
   subtree cnt.first lets us skip whole blocks.

8) count_less(s)
   At every position:
   - words ending at the current prefix are smaller (shorter prefix)
   - every child with character < s[i] contributes its whole subtree
   Then continue through s[i].

9) Your cnt.second
   Kept exactly as in your template:
       sum of FULL string lengths among strings passing through the node.
   For prefix p, prefix_stats(p).second gives that sum directly.

===============================================================
*/
