struct SuffixAutomaton {
    struct State {
        int len;          // Longest string in this state
        int link;         // Suffix link
        int next[26];     // Transitions (assuming lowercase 'a'-'z')
        int cnt;          // Number of occurrences in the original string
        int first_pos;    // 0-indexed ending position of the first occurrence
        bool is_clone;    // True if this state was created by splitting another state

        State() {
            len = 0;
            link = -1;
            memset(next, -1, sizeof(next));
            cnt = 0;
            first_pos = -1;
            is_clone = false;
        }
    };

    vector<State> st;
    int sz;
    int last;

   
    // 1. INITIALIZATION & BUILDING 
    SuffixAutomaton(const string& s) {
        // A string of length N creates at most 2*N - 1 states.
        st.reserve(2 * s.length() + 1); 
        st.push_back(State());
        sz = 1;
        last = 0;

        for (char c : s) {
            extend(c);
        }
        build_topology_and_counts();
    }

    void extend(char ch) {
        int c = ch - 'a';
        int cur = sz++;
        st.push_back(State());
        
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = st[cur].len - 1; // 0-indexed end position
        st[cur].cnt = 1; // Physical characters represent 1 new occurrence

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st.push_back(State());
                st[clone].len = st[p].len + 1;
                st[clone].first_pos = st[q].first_pos; // Clones appear where the original first appeared
                st[clone].is_clone = true;
                st[clone].cnt = 0;                     // Clones don't add new occurrences directly
                for (int i = 0; i < 26; i++) st[clone].next[i] = st[q].next[i];
                st[clone].link = st[q].link;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // $O(N)$ post-processing to calculate exact frequencies via Suffix Links
    void build_topology_and_counts() {
        vector<int> count(sz, 0);
        vector<int> topo_order(sz);
        
        // Counting sort by length
        for (int i = 0; i < sz; i++) count[st[i].len]++;
        for (int i = 1; i < sz; i++) count[i] += count[i - 1];
        for (int i = 0; i < sz; i++) topo_order[--count[st[i].len]] = i;

        // Propagate counts from longest to shortest along the suffix links
        for (int i = sz - 1; i > 0; i--) {
            int u = topo_order[i];
            int link = st[u].link;
            if (link != -1) {
                st[link].cnt += st[u].cnt;
            }
        }
    }

    // 2. Common Functions

    // Checks if pattern p is a substring of the original string. O(|p|)
    bool contains(const string& p) {
        int u = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (st[u].next[c] == -1) return false;
            u = st[u].next[c];
        }
        return true;
    }

    // Returns the exact number of times pattern p appears. O(|p|)
    int count_occurrences(const string& p) {
        int u = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (st[u].next[c] == -1) return 0; // Doesn't exist
            u = st[u].next[c];
        }
        return st[u].cnt;
    }

    // Returns the 0-indexed STARTING position of the FIRST occurrence of pattern p. O(|p|)
    // Returns -1 if it doesn't exist.
    int first_occurrence_start(const string& p) {
        int u = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (st[u].next[c] == -1) return -1;
            u = st[u].next[c];
        }
        // first_pos stores the ENDING position, so we subtract length - 1 to get start
        return st[u].first_pos - p.length() + 1;
    }

    // Returns the total number of distinct substrings in the original string. O(N)
    long long count_distinct_substrings() {
        long long total = 0;
        for (int i = 1; i < sz; i++) {
            total += st[i].len - st[st[i].link].len;
        }
        return total;
    }

    // Finds the Longest Common Substring (LCS) between the built string and a new string T. O(|T|)
    string longest_common_substring(const string& T) {
        int u = 0;
        int l = 0;
        int max_l = 0;
        int best_pos = -1;

        for (int i = 0; i < (int)T.length(); i++) {
            int c = T[i] - 'a';
            while (u != -1 && st[u].next[c] == -1) {
                u = st[u].link;
                if (u != -1) l = st[u].len;
            }
            if (u == -1) {
                u = 0;
                l = 0;
            } else {
                u = st[u].next[c];
                l++;
            }
            if (l > max_l) {
                max_l = l;
                best_pos = i; // Ending position of the match in T
            }
        }
        if (max_l == 0) return "";
        return T.substr(best_pos - max_l + 1, max_l);
    }
};
