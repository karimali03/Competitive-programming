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
        int mx,mx2,frq1,frq2;
    };

    int n;
    vector<node> tree;
    node neutral = {0 , 0 , 0 ,0}; 
    int sz;
    SegmentTree(int size){
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        map<int,int>mp;
        mp[a.mx] += a.frq1; mp[a.mx2] += a.frq2;
        mp[b.mx] += b.frq1; mp[b.mx2] += b.frq2;
        return { (mp.rbegin())->first , (next(mp.rbegin()))->first ,
          (mp.rbegin())->second , (next(mp.rbegin()))->second };
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
                if (tl < (int)a.size()) tree[v] = {a[tl],0,1,0};
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
            tree[v] = {val , 0 , 1 , 0};
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
    SegmentTree st(n);
    st.build(v);
    while(q--){
        int op,x,y; cin>>op>>x>>y;
        if(op == 1){
            st.update(x-1,y);
        }else{
            cout<<st.query(x-1,y-1).frq2<<"\n";
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