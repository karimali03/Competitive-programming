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

struct SegmentTree {
    struct node {
        int val,idx;
    };

    int n;
    vector<node> tree;
    node neutral = {0 , 0}; 
    int sz;
    bool mx;
    SegmentTree(int size,bool mx):mx(mx){
        sz = size;
        n = 1;
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

    // Point update: set position pos to new_val
    void update(int pos,int new_val,int idx,int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = {new_val,idx};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(pos, new_val,idx,v * 2 + 1, tl, tm);
            else
                update(pos, new_val,idx,v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    void update(int pos,int new_val,int idx){
        update(pos,new_val,idx,0,0,sz-1);
    }
};


void solve(int test_case) {
    int n,d; cin>>n>>d;
    vi v(n); cin>>v;
    vi vals;
    f(i,0,n){
        vals.push_back(v[i]);
        vals.push_back(v[i]+d);
        vals.push_back(v[i]-d);
    } 

    compress cm(vals);
    vi dp(n),nxt(n,-1);
    SegmentTree st(cm.sz,true);
    dp[n-1] = 1;
    st.update(cm.idx(v[n-1]),1,n-1);
    for(int i = n-2 ; i >= 0 ; i--){
        dp[i] = 1;
        int ch1 = v[i] + d;
        auto it = st.query(cm.idx(ch1),cm.sz-1);
        int ch2 = v[i] - d;
        auto it2 = st.query(0,cm.idx(ch2));
        if(it.val > it2.val && it.val != 0){
            dp[i] = 1 + dp[it.idx];
            nxt[i] = it.idx;
        }else if(it2.val != 0){
            dp[i] += dp[it2.idx];
            nxt[i] = it2.idx;
        }
        int idx = cm.idx(v[i]);
        if(st.query(idx,idx).val < dp[i]){
            st.update(idx,dp[i],i);
        }
    }

    int mx = *max_element(all(dp));
    cout<<mx<<ln;
    for(int i = 0 ;i < n ; i++){
        if(dp[i] == mx){
            cout<<i+1<<" ";
            int cur = nxt[i];
            while (cur != -1){
                cout<<cur+1<<" ";
                cur = nxt[cur];
            }
            break;
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