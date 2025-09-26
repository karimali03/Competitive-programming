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
    struct node { int val = 0; };
    vector<node> tree;
    vector<pair<int,int>> lazy;            // {a1, d}
    node neutral = {0};
    pair<int,int> no_operation = {0,0};
    int sz;

    SegmentTree(int size) {
        sz = size;
        tree.assign(4 * max(1ll, size), neutral);   // safe sizing
        lazy.assign(4 * max(1ll, size), no_operation);
    }

    node merge(const node &a, const node &b) {
        return { a.val + b.val };
    }

    // apply pending lazy[v] to node v (do NOT recursively push children)
    void push(int v, int tl, int tr) {
        if (lazy[v] == no_operation) return;
        ll a1 = lazy[v].first;
        ll d  = lazy[v].second;
        ll len = tr - tl + 1;
        ll added = len * a1 + d * ( (len * (len - 1)) / 2 );
        tree[v].val += added;

        if (tl != tr) {
            int tm = (tl + tr) / 2;
            int left_len = tm - tl + 1;
            // left child gets same a1,d relative to its tl
            lazy[v*2+1].first += a1;
            lazy[v*2+1].second += d;
            // right child's first term shifts by left_len
            lazy[v*2+2].first += a1 + d * left_len;
            lazy[v*2+2].second += d;
        }
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = { a[tl] };
            else tree[v] = neutral;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2+1, tl, tm);
            build(a, v*2+2, tm+1, tr);
            tree[v] = merge(tree[v*2+1], tree[v*2+2]);
        }
    }
    void build(vector<int> &a) { build(a, 0, 0, sz-1); }

    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return neutral;
        push(v, tl, tr);
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v*2+1, tl, tm, l, min(r, tm));
        node right = query(v*2+2, tm+1, tr, max(l, tm+1), r);
        return merge(left, right);
    }
    node query(int l, int r) { return query(0, 0, sz-1, l, r); }

    // x is the first term at index 'l' (global). d == 1 for your problem.
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) return;
        push(v, tl, tr);
        if (l == tl && r == tr) {
            // set lazy for this node; don't force-push children now
            lazy[v].first += x;
            lazy[v].second += 1;
            return;
        }
        int tm = (tl + tr) / 2;
        // update left part (x is still the first term at global l)
        update(v*2+1, tl, tm, l, min(r, tm), x);
        // how many terms from [l,r] lie in left child? clamp to >= 0
        long long left_contrib = max(0LL, (long long)min(tm, r) - l + 1);
        // right part first term is shifted by left_contrib
        update(v*2+2, tm+1, tr, max(l, tm+1), r, x + left_contrib);
        tree[v] = merge(tree[v*2+1], tree[v*2+2]);
    }
    void update(int l, int r, int idx) { update(0, 0, sz-1, l, r, idx); }
};


void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    SegmentTree st(n); st.build(v);
    while(q--){
        int a,b,c; cin>>a>>b>>c; b--,c--;
        if(a == 1){
            st.update(b,c,1);
        }else{
            cout<<st.query(b,c).val<<ln;
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