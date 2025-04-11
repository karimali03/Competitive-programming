// Seg Tree to find first element greater than x
struct SegmentTree {
    int n;
    int tree[300005*4]{};
    int neutral = 0;  // Change for different operations
 
    int merge(const int &a, const int &b) {
        return { max(  a , b ) }; // Change operation if needed
    }
 
    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
 
    // Query in range [l, r]
    int order_of_key(int v, int tl, int tr, int val) {
        if ( tree[v] <= val ) return -1;
        if (tl == tr) return tl;
        int tm = (tl + tr) / 2;
        int left = order_of_key(v * 2 + 1, tl, tm, val );
        if(left == -1)
        left =  order_of_key(v * 2 + 2, tm + 1, tr, val);
        return left;
    }
 
    // Point update at position pos
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] += new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2 + 1, tl, tm, pos, new_val);
            else
                update(v * 2 + 2, tm + 1, tr, pos, new_val);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
 
 
};
 
