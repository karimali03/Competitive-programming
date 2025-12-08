struct Trie {
    static const int MAX_BITS = 30;
    struct node {
        int nxt[2];
        bool leaf;
        int cnt;
        node() {
            leaf = false;
            cnt = 0;
            nxt[0] = nxt[1] = -1;
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(int num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(child[cur].nxt[bit] == -1){
                child[cur].nxt[bit] = child.size();
                child.push_back(node());
            }
            cur = child[cur].nxt[bit];
            child[cur].cnt++;
        }
    }
   
    int mex(int xor_val){
        int cur = 0;
        int ret = 0;
        for(int i = MAX_BITS ; i >= 0 ; i--){
            if(cur == -1) break;
            int bit = (xor_val >> i)&1;
            bool full = false;
            int cap = (1LL << i);
            if(child[cur].nxt[bit] != -1 && child[child[cur].nxt[bit]].cnt == cap) full = true;
            if(full){
                ret |= (1LL << i);
                cur = child[cur].nxt[1-bit];
            }else cur = child[cur].nxt[bit];
        }
        return ret;
    }

    bool search(int num){
        int cur = 0;
        for(int shift = MAX_BITS ; shift >= 0 ; shift--){
            int bit = (num>>shift)&1;
            if(child[cur].nxt[bit] == -1) return false;
            cur = child[cur].nxt[bit];
        }
        return true; 
    }

    int find_max_xor(int num){
        int ret = 0;
        int cur = 0;
        for(int sh = MAX_BITS ; sh >= 0 ; sh--){
            if (cur == -1) break; 
            int bit = (num >> sh)&1;
            
            if(child[cur].nxt[1-bit] != -1){
                ret |= (1 << sh);
                cur = child[cur].nxt[1-bit];
            }else{
                cur = child[cur].nxt[bit];
            }
        }
        return ret;
    }

};

