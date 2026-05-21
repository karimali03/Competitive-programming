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
        int val, idx;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;

    // Constructor pads size to the next power of 2
    SegmentTree(int size){
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = {0};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        return {  a.val + b.val , a.idx };
    }

    // Build array in O(N)
    void build(const vector<int>& a) {
        // indexing from n to 2n-1 for leaves
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i], i};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Point update: set position pos to new_val in O(log N)
    void update(int pos) {
        pos += n; // Jump directly to leaf
        tree[pos].val ^= 1;
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

    // Helper condition for Query 2 (handles both Max and Min trees)
    bool chk(int idx,int len) {
        return tree[idx].val < len; 
    }

    // Query 2: Find first element == 0 in [l, r]
    pair<int, int> query2(int l, int r) {
        // Now storing pairs of {node_index, node_segment_length}
        vector<pair<int, int>> left_nodes, right_nodes;
        
        int current_len = 1; // Leaves start with a length of 1
        
        // As we move up the tree (l >>= 1, r >>= 1), the segment length doubles (current_len <<= 1)
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1, current_len <<= 1) {
            if (l & 1) {
                left_nodes.push_back({l++, current_len});
            }
            if (r & 1) {
                right_nodes.push_back({--r, current_len});
            }
        }

        // walk_down now takes the node index AND the length of the segment it covers
        auto walk_down = [&](int v, int len) {
            while (v < n) { 
                len >>= 1; // A child covers exactly half the length of its parent
                int left_child = v << 1;
                
                // If the left child's sum is LESS than its length, it hides a 0. Go left.
                if (chk(left_child, len)) {
                    v = left_child;
                } else { // Otherwise, the 0 must be in the right child. Go right.
                    v = left_child | 1;
                }
            }
            return make_pair(tree[v].val, tree[v].idx);
        };

        // Check left nodes
        for (auto [v, len] : left_nodes) {
            if (chk(v, len)) {
                return walk_down(v, len);
            }
        }

        // Check right nodes (read backwards)
        for (int i = (int)right_nodes.size() - 1; i >= 0; --i) {
            auto [v, len] = right_nodes[i];
            if (chk(v, len)) {
                return walk_down(v, len);
            }
        }

        return {-1, -1}; 
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
    
    
};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    HLD hld(n,g);
    vi a(n); 
    f(i,0,n) a[i] = 1;
    SegmentTree st(n);
    st.build(a);
    vi mp(n);
    f(i,0,n) mp[hld.in[i]] = i;
  

    while(q--){
        int op; cin>>op;
        if(op == 1){
            int x; cin>>x; x--;
            auto rngs = hld.query(0,x);
            sort(all(rngs));
            int res = -1;
            for(auto &[l,r] : rngs){
                auto [val, idx] = st.query2(l, r);
                if(val == -1) continue; 
                res = mp[idx] + 1;
                break;
            }
            cout << res << ln;
        }else{
            int x; cin>>x; x--;
            st.update(hld.in[x]);
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