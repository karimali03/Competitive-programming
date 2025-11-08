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
        vi val;
        int idx;
    };

    int n;
    vector<node> tree;
    node neutral;
    int sz;
    bool mx;
    SegmentTree(int size){
        sz = size;
        n = 1;
        neutral = { {INT32_MIN} , -1 };
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        sort(rall(a.val));
        sort(rall(b.val));
        if(a.val.back() > a.val.back()) return { {a.val.back()} , a.idx};
        else return { {b.val.back()} , b.idx};
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = { {INT32_MIN} , tl};
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
    void update(int pos,int v, int tl, int tr){
        if (tl == tr) {
            tree[v].val.pop_back();
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos,v * 2 + 1, tl, tm);
            else
                update(pos,v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int pos){
        update(pos,0,0,sz-1);
    }
    void update(int pos,int new_val,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].val.push_back(new_val);
            sort(rall(tree[v].val));
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos,new_val,v * 2 + 1, tl, tm);
            else
                update(pos,new_val,v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int pos,int new_val){
        update(pos,new_val,0,0,sz-1);
    }
};

struct compress {
    vector<int> org;
    map<int,int>mp;
    int sz;
    compress(vector<int> v){
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        for(int i = 0 ;i < (int)v.size() ; i++) mp[v[i]] = i;
        for(auto &[a,b] : mp) org.push_back(a);
        sz = v.size();
    }
    int idx(int val){
        return mp[val];
    }

    int val(int idx){
        return org[idx];
    }
};


void solve(int test_case) {
    int n,m; cin>>n>>m;
    vi a(n),b(m),c(m); cin>>a>>b>>c;
    vi val;
    for(auto it : a) val.push_back(it);
    for(auto it : b) val.push_back(it);
    for(auto it : c) val.push_back(it);
    compress st(val);

    priority_queue<int>q;
    for(auto it : a) q.push(st.idx(it));
    SegmentTree seg(st.sz);
    seg.build();
    int cnt = 0;
    while(!q.empty()){
        auto it = q.top(); q.pop();
        auto x = seg.query(0 , it);
        if(x.val.back() == INT32_MIN) continue;
        cnt++;
        if(x.val.back() > 0) q.push(max(it , x.val.back()));
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