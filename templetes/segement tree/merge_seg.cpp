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
  //  cin >> t;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}


struct SegmentTree {
    struct node {
        vi v;
    };

    int n;
    vector<node> tree;
    node neutral = { {INT_MIN} };  // Change for different operations

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        vi merged;
        int i = 0 , j = 0 , k = 0;
        while(i < a.v.size() && j < b.v.size()){
            if(a.v[i] < b.v[j])  merged.push_back(a.v[i++]);
            else merged.push_back(b.v[j++]);
        }
        while(i < a.v.size()) merged.push_back(a.v[i++]);
        while(j < b.v.size()) merged.push_back(b.v[j++]);

        return { merged };
    }

    // Build the segment tree from a given array
    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = { {a[tl]} };
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    // Query in range [l, r]
    int query(int v, int tl, int tr, int l, int r , int k) {
        if (l > r) return 0;
        if (l == tl && r == tr){
            auto bs = upper_bound(all(tree[v].v) , k) - tree[v].v.begin();
            return tree[v].v.size() - bs;
        }
        int tm = (tl + tr) / 2;
        auto left = query(v * 2 + 1, tl, tm, l, min(r, tm) , k);
        auto right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r , k);
        return left + right;
    }

};



void solve(int test_case){
    int n; cin>>n;
    vi v(n); cin>>v;
    SegmentTree seg(n);
    seg.build(v, 0, 0, n - 1);
    int q; cin>>q;
    while(q--){
        int l, r , k; cin>>l>>r>>k;
        auto ans = seg.query(0, 0, n - 1, l - 1, r - 1 , k);
        cout<<ans<<ln;
    }
}
