#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

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
        int val;
    };
    
    vector<node> tree;
    vector<pair<int,int>> lazy;
    node neutral = {0};
    pair<int,int> no_operation = {0,0};
    
    int n;
    int sz;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        return {a.val + b.val}; // Change operation if needed
    }

    void push(int v, int tl, int tr , int deg = 2) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            if(lazy[v].first == 1) tree[v].val = (tr-tl+1) * lazy[v].second;
            else tree[v].val += (tr - tl + 1) * lazy[v].second;
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                if(lazy[v].first == 1){
                    lazy[v*2+1] = lazy[v];
                    lazy[v*2+2] = lazy[v];
                }else{
                    lazy[v * 2 + 1].second += lazy[v].second;
                    lazy[v * 2 + 2].second += lazy[v].second;
                }
            }
            push(v * 2 + 1, tl, (tl + tr) / 2 , deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

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
    
    void build(vector<int> &a){
        build(a,0,0,sz-1);
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }
    
    node query(int l,int r){
        return query(0,0,sz-1,l,r);
    }
    // set [l,r] to x
    void update(int v, int tl, int tr, int l, int r, int x ,int type) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            if(type == 1) lazy[v] = {1,x};
            else lazy[v].second += x;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), x,type);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x,type);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void update(int l,int r,int idx,int type){
         update(0,0,sz-1,l,r,idx,type);
    }
};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    SegmentTree st(n);
    st.build(v);
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int l,r,x; cin>>l>>r>>x; l--,r--;
            st.update(l,r,x,0);
        }else if(op == 2){
            int l,r,x; cin>>l>>r>>x; l--,r--;
            st.update(l,r,x,1);
        }else{
            int l,r; cin>>l>>r; l--,r--;
            cout<<st.query(l,r).val<<ln;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}