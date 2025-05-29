struct Trie {
    private:
        
        Trie* child[26]; 
        bool isLeaf;
        char base; // '0' or 'a' or 'A'
    
    public:
        Trie(char baseChar = 'a') : isLeaf(false), base(baseChar) {
            memset(child,0,sizeof(child));
        }
    
        void insert(string str, int idx = 0) {
            Trie* ptr = this;
            int n = str.size();
            for (int i = idx; i < n; i++) {
                int index = (str[i] - base);
    
                if (!ptr->child[index]) {
                    ptr->child[index] = new Trie(base);
                }
                ptr = ptr->child[index];
                if (i == n - 1) ptr->isLeaf = true;
            }
        }
    
        bool word_exist(string str) {
            int n = str.size();
            Trie* ptr = this;
            for (int i = 0; i < n; i++) {
                int index = (str[i] - base );
                if (!ptr->child[index]) return false;
                ptr = ptr->child[index];
            }
            return ptr->isLeaf;
        }
    
        bool prefix_exist(string str) {
            int n = str.size();
            Trie* ptr = this;
            for (int i = 0; i < n; i++) {
                int index = (str[i] - base);
                if (!ptr->child[index]) return false;
                ptr = ptr->child[index];
            }
            return true;
        }
    
        void auto_complete(string s, vector<string>& res) {
            Trie* ptr = this;
            for (int i = 0; i < s.size(); i++) {
                int index = (s[i] - base );
                if (index == -1 || !ptr->child[index]) return; // Stop if prefix is invalid
                ptr = ptr->child[index];
            }
            ptr->get_all_strings(res, s);
        }
    
        void get_all_strings(vector<string>& res, string s = "") {
            if (isLeaf) res.push_back(s);
            for (int i = 0; i < 26; ++i) { // Change size to 10 for digits
                if (child[i]) {
                    char nextChar = i + base;
                    child[i]->get_all_strings(res, s + nextChar);
                }
            }
        }
    
    };
    
