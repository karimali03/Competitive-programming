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


vector<int> NGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,n);
    for(int i = 0 ; i < n ; i++){
        while(!st.empty() && v[st.top()] <= v[i]){ // > for NSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(vector<int> &v){
    int n = v.size();
    stack<int>st;
    vector<int>res(n,-1);
    for(int i = n-1 ; i >= 0 ; i--){
        while(!st.empty() && v[st.top()] < v[i]){ // > for PSE
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

struct SegmentTree {
    struct node {
        int val,idx;
    };

    int n;
    vector<node> tree;
    node neutral = {INT32_MIN}; 
    int sz;
    bool mx;
    SegmentTree(int size,bool mx):mx(mx){
        sz = size;
        n = 1;
        if(mx) neutral = {INT32_MIN};
        else neutral = {INT32_MAX};
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        if(mx) return a.val > b.val ? a : b;
        return a.val < b.val ? a : b;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
                if (tl < (int)a.size()) tree[v] = {a[tl],tl};
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

    // Query 2: Conditional query in [l, r] (e.g., find first index with value <= x)
    // Returns index or INT32_MAX if not found
    pair<int,int> query2(int l,int r,int x,int v, int tl, int tr) {
        if (l > r || l > tr || r < tl) return {-1,-1}; // Out of segment
        if (tree[v].val < x) return {-1,-1}; // Condition not met in this segment
        if (tl == tr) return {tree[v].val,tl}; // Leaf node with condition met
        int tm = (tl + tr) / 2;
        auto left = query2( l ,min(r,tm),x,v*2+1,tl,tm);
        if (left.first != -1) return left;
        auto right =  query2(max(l, tm + 1), r, x ,v * 2 + 2, tm + 1, tr);
        return right;
    }

    pair<int,int> query2(int l,int r,int x){
        return query2(l,r,x,0,0,sz-1);
    }

    // Point update: set position pos to new_val
    void update(int pos,int new_val,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {new_val};
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
    int n; cin>>n;
    vi v(n); cin>>v;
    auto ng = NGE(v);
    auto pg = PGE(v);
    int ans = 0;
    for(int i = 0 ; i < n ; i++){
        int l = pg[i]+1;
        int r = ng[i]-1;
        if(l != r){

        }
    }
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