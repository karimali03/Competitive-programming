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
        int sum,val,idx;
    };

    int n;
    vector<node> tree;
    node neutral = {0 , INT32_MIN , -1}; 
    int sz;
    bool mx;
    SegmentTree(int size,bool mx):mx(mx){
        sz = size;
        n = 1;
        if(mx) neutral = { 0 , INT32_MIN , -1};
        else neutral = {0  ,INT32_MAX , -1};
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        int sum = a.sum + b.sum;
        if(mx){
            if(a.val > b.val) return {sum , a.val , a.idx};
            return {sum , b.val , b.idx};
        }
        if(a.val < b.val) return {sum , a.val , a.idx};
        return {sum , b.val , b.idx};
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
                if (tl < (int)a.size()) tree[v] = {a[tl],a[tl],tl};
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
    void update(int pos,int new_val,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].sum = tree[v].val = new_val;
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
void solve(int test_case) {
    int n,m; cin>>n>>m;
    vi v(n); cin>>v;
    SegmentTree st(n,true);
    st.build(v);
    while(m--){
        int op; cin>>op;
        if(op == 1){
            int l,r; cin>>l>>r; l--,r--;
            cout<<st.query(l,r).sum<<ln;
        }
        else if(op == 2){
            int l,r,x; cin>>l>>r>>x; l--,r--;
            while(true){
                auto it = st.query(l,r);
                if(it.val < x) break;
                st.update(it.idx,it.val%x);
            }
        }
        else{
            int x,y; cin>>x>>y; x--;
            st.update(x,y);
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