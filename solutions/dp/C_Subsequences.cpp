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
        int val;
    };

    int n;
    vector<node> tree;
    node neutral = {0};  // Change for different operations

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return {a.val + b.val}; // Change operation if needed
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
    node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }

    // Point update at position pos
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v].val +=new_val;
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





void solve(int test_case){
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vector<SegmentTree> st(k+5,SegmentTree(n+5));
    st[0].update(0,0,n+1,0,1);
    for(int i = 0 ; i < n ; i++){
        for(int x = 1 ; x <= k+1 ; x++){
            int val = st[x-1].query(0,0,n+1,0,v[i]-1).val;
            st[x].update(0,0,n+1,v[i],val);
        }
    }
    cout<<st[k+1].query(0,0,n+1,0,n+1).val<<ln;
}