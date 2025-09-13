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



const int N = 21;
struct SegmentTree {
    struct node {
        int cnt[N]{};
    };
    
    vector<node> tree;
    vector<int> lazy;
    node neutral = {};
    int no_operation = 0;
    
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
        node ret;
        for(int i  = 0; i < 21 ; i++) ret.cnt[i] = a.cnt[i] + b.cnt[i];
        return ret; // Change operation if needed
    }

    void push(int v, int tl, int tr , int deg = 2) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            for(int i = 0 ; i < 21 ; i++){
                if((lazy[v]>>i)&1){
                    tree[v].cnt[i] = (tr-tl+1) - tree[v].cnt[i];
                }
            }
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                    lazy[v * 2 + 1] ^= lazy[v];
                    lazy[v * 2 + 2] ^= lazy[v];
                }
            push(v * 2 + 1, tl, (tl + tr) / 2 , deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()){
                for(int i = 0 ; i < 21 ; i++){
                    if((a[tl]>>i)&1) tree[v].cnt[i] = 1; 
                }
            }
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
    void update(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v] ^= x;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), x);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void update(int l,int r,int idx){
         update(0,0,sz-1,l,r,idx);
    }
};



void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    SegmentTree st(n);
    st.build(v);
    int q; cin>>q;
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int l,r; cin>>l>>r; l--,r--;
            auto ret = st.query(l,r);
            ll sum = 0;
            for(int i = 0; i < 21 ; i++) sum += (ll)(1<<i) * (ll)ret.cnt[i];
            cout<<sum<<ln;
        }else{
            int l,r,x; cin>>l>>r>>x; l--,r--;
            st.update(l,r,x);
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