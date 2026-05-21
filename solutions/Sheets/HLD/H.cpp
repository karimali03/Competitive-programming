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
        long long sum, pref, suff, ans;
        int len;      // We must track length for range assignments
        bool is_null; // Identifies our neutral element
    };

    int n, h;
    vector<node> tree;
    vector<long long> lazy;
    vector<bool> has_lazy; // Boolean flag to distinguish "set to 0" from "no update"
    node neutral;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        h = __builtin_ctz(n);
        
        neutral = {0, 0, 0, 0, 0, true};
        tree.assign(2 * n, neutral);
        lazy.assign(n, 0);
        has_lazy.assign(n, false);
    }

    node merge(const node &l, const node &r) {
        if (l.is_null) return r;
        if (r.is_null) return l;

        node res;
        res.is_null = false;
        res.len = l.len + r.len;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans = max({l.ans, r.ans, l.suff + r.pref});
        return res;
    }

    // Apply a "Set to X" operation to a node
    void apply(int p, long long val) {
        tree[p].sum = (long long)tree[p].len * val;
        
        // If val >= 0, we take the whole segment. If val < 0, we take just one element.
        long long max_val = max(val, tree[p].sum); 
        tree[p].pref = tree[p].suff = tree[p].ans = max_val;

        if (p < n) {
            lazy[p] = val;
            has_lazy[p] = true;
        }
    }

    // Push pending assignments from root down to parents of p
    void push_path(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (has_lazy[i]) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                has_lazy[i] = false;
            }
        }
    }

    // Rebuild the tree bottom-up from p to root
    void build_up(int p) {
        while (p > 1) {
            p >>= 1;
            // Recalculate based on children
            tree[p] = merge(tree[p << 1], tree[p << 1 | 1]);
            
            // If this node currently has an unpushed lazy tag of its own, 
            // that tag overwrites the merged result from its children.
            if (has_lazy[p]) {
                tree[p].sum = (long long)tree[p].len * lazy[p];
                long long max_val = max(lazy[p], tree[p].sum);
                tree[p].pref = tree[p].suff = tree[p].ans = max_val;
            }
        }
    }

    // Build the initial tree in O(N)
    void build(const vector<long long>& a) {
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i], a[i], a[i], a[i], 1, false};
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Range Set: Set all elements in [l, r] inclusive to `val`
    void update_range(int l, int r, long long val) {
        l += n; r += n + 1; // Half-open interval [l, r+1)
        int l0 = l, r0 = r;

        push_path(l0); 
        push_path(r0 - 1);

        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }

        build_up(l0); 
        build_up(r0 - 1);
    }

    // Query: Get max subarray data in [l, r] inclusive
    node query(int l, int r) {
        l += n; r += n + 1;
        
        // Push tags to ensure fresh data at our query bounds
        push_path(l); 
        push_path(r - 1);
        
        node resL = neutral, resR = neutral;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]);
            if (r & 1) resR = merge(tree[--r], resR);
        }
        return merge(resL, resR);
    }
};

struct HLD {
    
    vi big,sz,depth,head,in,par;
    vii g;
    void init(int x,int d){
        sz[x] = 1;
        big[x] = -1;
        depth[x] = d;
        for(auto &it : g[x]){
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
        for(auto &it : g[x]){
            if(par[x] == it || it == big[x]) continue;
            head[it] = it;
            flatten(it,timer);
        }
    }

    HLD(int n,vii &g):g(g){
        big = sz = depth = in = par = head = vi(n);
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
                ret.push_back({in[x],in[y]});
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
    pair<vector<pair<int,int>>, vector<pair<int,int>>> query_directed(int u, int v) {
        vector<pair<int,int>> uSide, vSide;
        
        // Climb up independently
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                // u is deeper, append to uSide
                uSide.push_back({in[head[u]], in[u]});
                u = par[head[u]];
            } else {
                // v is deeper, append to vSide
                vSide.push_back({in[head[v]], in[v]});
                v = par[head[v]];
            }
        }
        
        // Handle the final segment at the LCA
        if (depth[u] > depth[v]) {
            uSide.push_back({in[v], in[u]});
        } else {
            vSide.push_back({in[u], in[v]});
        }
        
        return {uSide, vSide};
    }
    
    
};

void solve(int test_case) {
    int n; cin>>n;
    vi val(n); cin>>val;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    HLD hld(n,g);
    vi x(n);
    f(i,0,n) x[hld.in[i]] = val[i];
    SegmentTree st(n);
    st.build(x);
    int q; cin>>q;
  

    while(q--){
        int op; cin>>op;
        if(op == 1){
            int x,y; cin>>x>>y; x--,y--;
            auto res = hld.query_directed(x,y);
            SegmentTree::node lf = {0, 0, 0, 0, 0, true}; 
            SegmentTree::node rh = {0, 0, 0, 0, 0, true};

            for(auto &[l, r] : res.first) {
                auto node = st.query(l, r);
                swap(node.pref, node.suff); 
                lf = st.merge(lf, node);
            }
            for(auto &[l, r] : res.second) {
                auto node = st.query(l, r);
                swap(node.pref, node.suff);
                rh = st.merge(rh, node);
            }
            swap(rh.pref, rh.suff);
            auto ans = st.merge(lf, rh);
            cout << max( 0ll , ans.ans) << ln;

        }else{
            int x,y,z; cin>>x>>y>>z; x--,y--;
            auto rngs = hld.query(x, y);  
            for(auto &[l, r] : rngs) {
                st.update_range(l, r, z);
            }
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