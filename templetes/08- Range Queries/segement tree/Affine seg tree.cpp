
const int MOD = 1e9 + 7;
struct SegmentTree {
    struct node {
        int val; 
    };
    struct lzy {
        int mul, add;
    };
    
    vector<node> tree;
    vector<lzy> lazy;
    node neutral = {0};
    lzy no_operation = {1, 0}; 
    
    int n;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

 
    void push(int v, int tl, int tr) {
        if (lazy[v].mul == 1 && lazy[v].add == 0) return;

        int len = tr - tl + 1;
        

        // Sum_new = Sum_old * Mul + Add * Length
        int term1 = (tree[v].val * lazy[v].mul) % MOD;
        int term2 = (lazy[v].add * len) % MOD;
        tree[v].val = (term1 + term2) % MOD;

        // 2. Push to children
        if (tl != tr) {
            int left = 2 * v + 1;
            int right = 2 * v + 2;

            // Apply Parent's (Mul, Add) to Child's existing (m, a)
            // New_Mul = Old_Mul * Parent_Mul
            // New_Add = Old_Add * Parent_Mul + Parent_Add
            
            // Left Child
            lazy[left].mul = (lazy[left].mul * lazy[v].mul) % MOD;
            lazy[left].add = (lazy[left].add * lazy[v].mul + lazy[v].add) % MOD;

            // Right Child
            lazy[right].mul = (lazy[right].mul * lazy[v].mul) % MOD;
            lazy[right].add = (lazy[right].add * lazy[v].mul + lazy[v].add) % MOD;
        }

        
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {a[tl] % MOD};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v].val = (tree[v * 2 + 1].val + tree[v * 2 + 2].val) % MOD;
        }
    }
    
    void build(vector<int> &a) {
        build(a, 0, 0, n - 1);
    }

    // Generic Update Handler
    // mul_val: multiplier to apply
    // add_val: value to add
    void _update(int v, int tl, int tr, int l, int r, int mul_val, int add_val) {
        push(v, tl, tr); // Always clean current node first
        
        if (l > r) return;

        if (l == tl && r == tr) {
            // Compose updates onto current lazy
            // Same logic as push: L.m = L.m * M_new, L.a = L.a * M_new + A_new
            lazy[v].mul = (lazy[v].mul * mul_val) % MOD;
            lazy[v].add = (lazy[v].add * mul_val + add_val) % MOD;

            // YOUR STYLE: Call push immediately to fix tree[v].val
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            _update(v * 2 + 1, tl, tm, l, min(r, tm), mul_val, add_val);
            _update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, mul_val, add_val);
            tree[v].val = (tree[v * 2 + 1].val + tree[v * 2 + 2].val) % MOD;
        }
    }
    
    // Public Wrapper for Range Add
    // To add X: Multiply by 1, Add X
    void range_add(int l, int r, int val) {
        _update(0, 0, n - 1, l, r, 1, val);
    }

    // Public Wrapper for Range Multiply
    // To multiply by X: Multiply by X, Add 0
    void range_mul(int l, int r, int val) {
        _update(0, 0, n - 1, l, r, val, 0);
    }

    int query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr); // Always clean current node first
        
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v].val;
        
        int tm = (tl + tr) / 2;
        return (query(v * 2 + 1, tl, tm, l, min(r, tm)) +
                query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r)) % MOD;
    }
    
    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

void solve(int test_case) {
    int n, q; cin >> n >> q;
    vi v(n); cin >> v;
    SegmentTree st(n);
    st.build(v);
    
    while (q--) {
        int op; cin >> op;
        if (op == 0) { 
            // Add: 0 L R VAL
            int l, r, val; cin >> l >> r >> val;
            st.range_add(l, r - 1, val);
        } else if (op == 1) {
            // Multiply: 1 L R VAL
            int l, r, val; cin >> l >> r >> val;
            st.range_mul(l, r - 1, val);
        } else {
            // Query Sum: 2 L R
            int l, r; cin >> l >> r;
            cout << st.query(l, r - 1) << ln;
        }
    }
}
