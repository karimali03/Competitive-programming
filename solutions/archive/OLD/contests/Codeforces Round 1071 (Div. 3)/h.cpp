#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define vec vector
#define vi vector<int>
#define all(x) (x).begin(), (x).end()
#define int long long

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

struct SegmentTree {
    struct node { 
        ll val = 0; 
    };
    
    struct LazyTag {
        ll mul = 1;
        ll base = 0;
        ll step = 0;
        
        bool empty() const {
            return mul == 1 && base == 0 && step == 0;
        }
        
        void reset() {
            mul = 1; base = 0; step = 0;
        }
    };

    int sz;
    vector<node> tree;
    vector<LazyTag> lazy;

    SegmentTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        // Safety: ensure 2*sz is allocated. 
        // Using sz for recursion bounds ensures indices stay within 2*sz.
        tree.assign(2*sz, node());
        lazy.assign(2*sz, LazyTag());
    }

    node merge(const node &a, const node &b) {
        return { a.val + b.val }; 
    }

    ll sum_ap(ll n, ll a, ll d) {
        ll term1 = n * a;
        ll term2 = d * ((n * (n - 1)) / 2);
        return term1 + term2; 
    }

    void apply_to_node(int v, int tl, int tr, const LazyTag &op) {
        if (op.empty()) return;
        
        ll len = tr - tl + 1;
        
        // 1. Update Node Value
        tree[v].val = tree[v].val * op.mul + sum_ap(len, op.base, op.step);
        
        // 2. Update Lazy Tag (Composition: New(Old(x)))
        lazy[v].mul = lazy[v].mul * op.mul;
        lazy[v].base = lazy[v].base * op.mul + op.base;
        lazy[v].step = lazy[v].step * op.mul + op.step;
    }

    void push(int v, int tl, int tr) {
        if (lazy[v].empty()) return;
        
        int tm = (tl + tr) >> 1;
        int left = v*2+1;
        int right = v*2+2;
        
        // Left Child
        apply_to_node(left, tl, tm, lazy[v]);
        
        // Right Child (Base must be shifted by length of left child)
        ll left_len = (tm - tl + 1);
        LazyTag right_op = lazy[v];
        right_op.base = lazy[v].base + left_len * lazy[v].step;
        
        apply_to_node(right, tm+1, tr, right_op);
        
        lazy[v].reset();
    }

    void build(vector<int> &a_in) {
        vector<ll> a(a_in.begin(), a_in.end());
        build_rec(a, 0, 0, sz-1);
    }

    void build_rec(vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v].val = a[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build_rec(a, v*2+1, tl, tm);
        build_rec(a, v*2+2, tm+1, tr);
        tree[v] = merge(tree[v*2+1], tree[v*2+2]);
    }

    // Pass specific ranges [l, r], but recursion bounds are [tl, tr]
    void update_ap(int v, int tl, int tr, int l, int r, ll base, ll step) {
        if (l > r) return;
        if (l == tl && r == tr) {
            LazyTag op;
            op.mul = 1; 
            op.base = base; 
            op.step = step;
            apply_to_node(v, tl, tr, op);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        
        // Split logic: Right child base calculation
        int l_r = min(r, tm);
        int r_l = max(l, tm+1);

        if (l <= l_r) {
            update_ap(v*2+1, tl, tm, l, l_r, base, step);
        }
        
        if (r_l <= r) {
            ll shift = max(0LL, (ll)r_l - l);
            ll base_for_right = base + shift * step;
            update_ap(v*2+2, tm+1, tr, r_l, r, base_for_right, step);
        }
        tree[v] = merge(tree[v*2+1], tree[v*2+2]);
    }

    void update_mul(int v, int tl, int tr, int l, int r, ll val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            LazyTag op;
            op.mul = val;
            apply_to_node(v, tl, tr, op);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        update_mul(v*2+1, tl, tm, l, min(r, tm), val);
        update_mul(v*2+2, tm+1, tr, max(l, tm+1), r, val);
        tree[v] = merge(tree[v*2+1], tree[v*2+2]);
    }

    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v].val;
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        return query(v*2+1, tl, tm, l, min(r, tm)) + 
               query(v*2+2, tm+1, tr, max(l, tm+1), r);
    }
};

void solve() {
    // int n, q;  cin>>n>>q;
    // SegmentTree seg(n);
 

    // while(q--) {
    //     int l, r; cin >> l >> r; l--, r--;
    //     int st = l;
    //     int pd = 1;
    //     int x = 1;
    //     while(st <= r){
    //         int en = st + pd - 1;
    //         seg.update_ap(0,0,seg.sz-1,st,min(r,en),x*pd,pd);
    //         st = en + 1;
    //         x += pd;
    //         pd *= 2;
    //         cout<<x<<" - ";
    //     }
    //     cout<<ln;
    //      for(int i = 0; i < n; i++) {
    //         cout << seg.query(0, 0, seg.sz - 1, i, i) << " ";
    //     }
    //     cout<<ln;
    // }

    for(int i = 1 ; i < 1000 ; i++){
        int x = i;
        int a = 0;
        while(x%2 == 0){
            x/=2;
            a++; 
        }
        cout<<(1ll<<a)<<" "<<(1ll<<a)*i<<ln;
    }
    
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin>>t;
    while (t--) solve();
    return 0;
}