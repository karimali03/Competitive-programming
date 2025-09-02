struct SegmentTree {
    struct node {
        int val,idx;
    };

    int n;
    vector<node> tree;
    node neutral = {INT32_MIN}; 
    int sz;
    bool mx;
    SegmentTree(int size,bool mx):mx(mx){
        n = 1;
        sz = n;
        if(mx) neutral = {INT32_MIN};
        else neutral = {INT32_MAX};
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        if(mx) return a.val > b.val ? a : b;
        return a.val < b.val ? a : b;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
                if (tl < (int)a.size()) tree[v] = {a[tl],tl};
                else tree[v] = neutral;
        } else {
                int tm = (tl + tr) / 2;
                build(a, v * 2 + 1, tl, tm);
                build(a, v * 2 + 2, tm + 1, tr);
                tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void build(vector<int>&a){
        return build(a,0,0,sz-1);
    }

    // Query 1: Range query in [l, r]
    node query(int l,int r,int v, int tl, int tr) {
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(l, min(r, tm),v * 2 + 1, tl, tm);
        node right = query(max(l, tm + 1), r,v * 2 + 2, tm + 1, tr);
        return merge(left, right);
    }

    node query(int l,int r){
        return query(l,r,0,0,sz-1);
    }

    // Query 2: Conditional query in [l, r] (e.g., find first index with value <= lf)
    // Returns index or INT32_MAX if not found
    pair<int,int> query_conditional(int l,int r,int lf,int v, int tl, int tr) {
        if (l > r || l > tr || r < tl) return {-1,-1}; // Out of segment
        if (tree[v].val <= lf) return {-1,-1}; // Condition not met in this segment
        if (tl == tr) return {tree[v].val,tl}; // Leaf node with condition met
        int tm = (tl + tr) / 2;
        auto rh_res = query_conditional(max(l, tm + 1), r, lf,v * 2 + 2, tm + 1, tr);
        if (rh_res.first != -1) return rh_res;
        return  query_conditional(l, min(r, tm), lf,v * 2 + 1, tl, tm);
    }

    pair<int,int> query_conditional(int l,int r,int lf){
        return query_conditional(l,r,lf,0,0,sz-1);
    }

    // Point update: set position pos to new_val
    void update(int pos,int new_val,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {new_val};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos, new_val,v * 2 + 1, tl, tm);
            else
                update(pos, new_val,v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int pos,int new_val){
        update(pos,new_val,0,0,sz-1);
    }
};
