struct SegmentTree {
    struct node {
        int pre,suf,sum,mx;
    };

    int n;
    vector<node> tree;
    node neutral = {INT32_MIN , INT32_MIN, INT32_MIN , INT32_MIN}; 
    int sz;
    SegmentTree(int size){
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        return {  max(a.pre , a.sum + b.pre ) , max(b.suf , b.sum + a.suf ) , 
                  a.sum + b.sum , max({a.mx,b.mx,a.suf+b.pre}) };
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
                if (tl < (int)a.size()) tree[v] = {a[tl],a[tl],a[tl],a[tl]};
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


    // Point update: set position pos to new_val
    void update(int pos,int val,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {val , val , val , val};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos, val,v * 2 + 1, tl, tm);
            else
                update(pos, val,v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int pos,int new_val){
        update(pos,new_val,0,0,sz-1);
    }

};

