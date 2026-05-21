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


const int INF = 1e9;
struct SegmentTree {
    struct node {
        int sum , pref , suf , ans;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;
   

    // Constructor pads size to the next power of 2
    SegmentTree(int size)  {
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = {0,-INF,-INF,-INF};
        tree.assign(2 * n, neutral);
        build(size);
    }

    // Build array in O(N)
    void build(int size) {
        // Place leaves
        for (int i = 0; i < size; i++) {
            tree[n + i] = {-INF,-INF,-INF,-INF};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    node merge(const node &a, const node &b) {
        return {
            a.sum + b.sum , 
            max(a.pref , a.sum + b.pref),
            max(b.suf , b.sum + a.suf) , 
            max({a.ans , b.ans , a.suf + b.pref})
        };
    }

    // Point update: set position pos to new_val in O(log N)
    void update(int pos, int new_val) {
        pos += n; // Jump directly to leaf
        tree[pos] = {new_val,new_val,new_val,new_val};
        // Climb up and update parents
        while (pos >>= 1) {
            tree[pos] = merge(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    // Query 1: Range query in [l, r] inclusive in O(log N)
    node query(int l, int r) {

        node resL = neutral, resR = neutral;
        // Convert to half-open interval [l, r+1)
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]); // Merge left side
            if (r & 1) resR = merge(tree[--r], resR); // Merge right side
        }
        return merge(resL, resR);
    }
};


void solve(int test_case) {
    int n; cin>>n;
    vector<array<int,2>> h(n);
    f(i,0,n){
        int x; cin>>x;
        h[i] = {x,i};
    }
    sort(rall(h));
    
    int q; cin>>q;
    vector<array<int,3>> x(q);
    f(i,0,q){
        int l,r,w; cin>>l>>r>>w; l--,r--;
        x[i] = {w , l , r};
    }
 
    // current l,r,ans for each query
    vector<int> L(q),R(q),ans(q);
    // buckets for each mid value ; store query indices
    vii buckets(n);
    f(i,0,q) L[i]=0,R[i]=n-1;
    // returns true if there are still queries to process
    auto update = [&]() -> bool{
        bool vld = false;
        for(int i = 0;i < q ; i++){
            if(L[i] <= R[i]){
                buckets[(L[i]+R[i])>>1].push_back(i);
                vld = true;
            }
        }
        return vld;
    };

    SegmentTree st(n);
    while(update()){
        st.build(n);
        // process each mid value
        for(int mid = 0; mid < n ; mid++){
            // update segment tree with current mid value
            st.update(h[mid][1],1);
            // process queries in the bucket for this mid
            for(auto &idx : buckets[mid]){
                auto [w,l,r] = x[idx];
                if(st.query(l,r).ans >= w){
                    ans[idx] = h[mid][0];
                    R[idx] = mid - 1;
                }else{
                    L[idx] = mid + 1;
                }
            }
            // clear bucket for next iteration
            buckets[mid].clear();
        }
    }

    for(int i = 0;i < q ; i++) cout<<ans[i]<<"\n";



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