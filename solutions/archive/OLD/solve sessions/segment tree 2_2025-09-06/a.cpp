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
        int mx,frq;
    };

    int n;
    vector<node> tree;
    node neutral = { INT32_MAX,0}; 
    int sz;
    SegmentTree(int size){
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        node ret = b;
        if(b.mx - a.mx < 20){
            ret.frq += a.mx / (1<<(b.mx-a.mx));
        }
        if(!ret.frq) return a;
        return ret;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
                tree[v] = { tl , 0 };
        } else {
                int tm = (tl + tr) / 2;
                build(v * 2 + 1, tl, tm);
                build(v * 2 + 2, tm + 1, tr);
                tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void build(){
        return build(0,0,sz-1);
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
            tree[v].frq += val;
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

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    SegmentTree st(200005);
    st.build();
    for(int i = 0 ; i < n ; i++) st.update(v[i],1);
    cout<<st.query(0,200004).mx<<" "<<st.query(0,200004)
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}