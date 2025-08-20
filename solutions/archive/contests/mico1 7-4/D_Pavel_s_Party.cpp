#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

struct SegmentTree {
    struct node {
        int mn;
        int idx;
    };
    
    int n;
    vector<node> tree;
    vector<int> lazy;
    node neutral = { 0 , {} };
    int no_operation = 0;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        if(a.mn <= b.mn) return a; 
        return b;
    }

    void push(int v, int tl, int tr , int deg = 1) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            tree[v].mn += lazy[v];
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                lazy[v * 2 + 1] += lazy[v];
                lazy[v * 2 + 2] += lazy[v];
            }
            push(v * 2 + 1, tl, (tl + tr) / 2, deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) {
                tree[v] = { a[tl] , tl } ;
            }
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return { INT_MAX , {}};
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v] += addend;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), addend);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, addend);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
};

void solve(int test_case){
    int n; cin>>n; 
    SegmentTree st(n);
    vi v(n); f(i,0,n) v[i] = i+1;
    st.build(v,0,0,n-1);
    vi res(n,-1);
    for(int i = 0 ; i < n ; i++){
        int a,b; cin>>a>>b; a--,b--;
        st.update(0,0,n-1,a,b,-1);
        auto mn = st.query(0,0,n-1,0,n-1);
        while(mn.mn == 0){
             res[mn.idx] = i+1;
             st.update(0,0,n-1,mn.idx,mn.idx,INT_MAX);
             mn = st.query(0,0,n-1,0,n-1);
            }
    }

    for(int i = 0 ; i < n ; i++){
        cout<<res[i]<<" ";
    }
}