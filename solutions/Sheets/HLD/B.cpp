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
        int val;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;

    // Constructor pads size to the next power of 2
    SegmentTree(int size){
        n = 1;
        while (n < size) n <<= 1;
        neutral = {INT32_MIN};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
          return a.val > b.val ? a : b;
    }

    // Build array in O(N)
    void build(vector<int>& a) {
        // Place leaves
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i]};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Point update: set position pos to new_val in O(log N)
    void update(int pos, int new_val) {
        pos += n; // Jump directly to leaf
        tree[pos] = {new_val};
        // Climb up and update parents
        while (pos >>= 1) {
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    // Query 1: Range query in [l, r] inclusive in O(log N)
    node query1(int l, int r) {
        node resL = neutral, resR = neutral;
        // Convert to half-open interval [l, r+1)
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]); // Merge left side
            if (r & 1) resR = merge(tree[--r], resR); // Merge right side
        }
        return merge(resL, resR);
    }
};


struct HLD {
    
    vi big,sz,depth,head,in,par;
    vector<vector<array<int,3>>> g;
    vi val , mp;
    void init(int x,int d){
        sz[x] = 1;
        big[x] = -1;
        depth[x] = d;
        for(auto &[it,_,__] : g[x]){
            if(it == par[x]) continue;
            par[it] = x;
            init(it,d+1);
            sz[x] += sz[it];
            if(big[x] == -1 || sz[it] > sz[big[x]]) big[x] = it;
        }
    };
    
    void flatten(int x,int &timer){
        in[x] = ++timer;
        if(~big[x]){
            head[big[x]] = head[x];
            flatten(big[x],timer);
        } 
        for(auto &[it,v,id] : g[x]){
            if(par[x] == it) continue;
            if(it != big[x]){
                head[it] = it;
                flatten(it,timer);
            }
            val[in[it]] = v;
            mp[id] = in[it];
        }
    }
    HLD(int n,vector<vector<array<int,3>>> &g):g(g){
        big = sz = depth = in = par = head = vi(n);
        val = mp = vi(n);
        init(0,0);
        head[0] = 0;
        int timer = -1;
        flatten(0,timer);
    };
    
    
    vector<pair<int,int>> query(int x,int y){
        vector<pair<int,int>> ret;
        while(true){
            if(depth[x] > depth[y]) swap(x,y);
            if(head[x] == head[y]){
                if(in[x]+1 <= in[y]) ret.push_back({in[x]+1,in[y]});
                return ret;
            }
            if(depth[head[x]] < depth[head[y]]) swap(x,y);
            // x will not exceed lca
            // y may exceed lca
            ret.push_back({in[head[x]] , in[x]});
            x = par[head[x]];
        }
        return ret;
    }
    
    
};

void solve(int test_case) {
    int n; cin>>n;
    vector<vector<array<int,3>>> g(n);
    f(i,1,n){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        g[x].push_back({y,z,i-1});
        g[y].push_back({x,z,i-1});
    }
    HLD hld(n,g);
    SegmentTree st(n-1);
    st.build(hld.val);
    string op;
    while (cin>>op && op != "DONE"){
        if(op == "QUERY"){
            int x,y; cin>>x>>y; x--,y--;
            auto rngs = hld.query(x,y);
            int res = st.neutral.val;
            for(auto &[l,r] : rngs){
                res = max(res , st.query1(l,r).val);
            }
            cout<<res<<ln;
        }else{
            int x,it; cin>>x>>it; x--;
            st.update(hld.mp[x],it);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}