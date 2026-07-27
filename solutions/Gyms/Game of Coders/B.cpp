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


struct SegTree {
    int n, h;
    vector<long long> t; // Tree array
    vector<long long> d; // Lazy array
    
    // NEUTRAL VALUES    
    const long long VAL_NEUTRAL = 1e16; // Neutral for tree values (e.g., -2e18 for Max)
    const long long LAZY_DEFAULT = 0;    // Neutral for lazy tags (e.g., 0 for Add)

    // merge two nodes values
    long long merge_nodes(long long left, long long right) {
        return min(left, right);
    }

    // how lazy values combined
    long long merge_tags(long long current_tag, long long new_tag) {
        return current_tag + new_tag;
    }

    // add lazy value to node
    long long apply_tag_to_val(long long val, long long tag) {
        return val + tag;
    }
  
    SegTree(int n) : n(n) {
        h = 32 - __builtin_clz(n);
        t.assign(2 * n, VAL_NEUTRAL); 
        d.assign(n, LAZY_DEFAULT);     
    }

    void build() {
        // 1. Assign values to leaf nodes (indices n to 2n-1)
        for (int i = 0; i < n; ++i) {
            t[n + i] = 0;
        }
        // 2. Compute the internal nodes bottom-up (indices n-1 down to 1)
        for (int i = n - 1; i > 0; --i) {
            t[i] = merge_nodes(t[i << 1], t[i << 1 | 1]);
        }
    }

    void apply(int p, long long tag) {
        // Update the actual node value
        t[p] = apply_tag_to_val(t[p], tag); 
        
        // If it's not a leaf, accumulate the tag for its children
        if (p < n) {
            d[p] = merge_tags(d[p], tag); 
        }
    }

    void build_path(int p) {
        while (p > 1) {
            p >>= 1; 
            // 1. Merge the children's actual values
            long long merged_children = merge_nodes(t[p << 1], t[p << 1 | 1]);
            
            // 2. If this parent has an un-pushed tag, apply it to the merged result
            if (d[p] != LAZY_DEFAULT) {
                t[p] = apply_tag_to_val(merged_children, d[p]);
            } else {
                t[p] = merged_children;
            }
        }
    }

    void push_path(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s; 
            // Only push if there is an active lazy tag
            if (d[i] != LAZY_DEFAULT) { 
                apply(i << 1, d[i]);
                apply(i << 1 | 1, d[i]);
                d[i] = LAZY_DEFAULT; // Reset parent's tag
            }
        }
    }
    
    // [l,r] zero based (inclusive)
    void update(int l, int r, long long tag) {
        r++; // Adjust for inclusive range
        l += n; r += n;
        int l0 = l, r0 = r;

        push_path(l0);
        push_path(r0 - 1);

        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, tag);
            if (r & 1) apply(--r, tag);
        }

        build_path(l0);
        build_path(r0 - 1);
    }
    
    // [l,r] zero based (inclusive)
    long long query(int l, int r) {
        r++; // Adjust for inclusive range
        l += n; r += n;

        push_path(l);
        push_path(r - 1);

        long long res_left = VAL_NEUTRAL;
        long long res_right = VAL_NEUTRAL;

        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_left = merge_nodes(res_left, t[l++]);
            if (r & 1) res_right = merge_nodes(t[--r], res_right);
        }

        return merge_nodes(res_left, res_right);
    }
};



void solve(int test_case) {
    int n; cin>>n;
    ll m; cin>>m;
    vi C(n),T(n);
    int mx = 0;
    ll sum = 0;
    for(int i = 0;i < n ; i++){
        cin>>T[i]>>C[i];
        mx = max(mx , C[i]);
        sum += C[i];
    }
    if(sum <= m){
        cout<<0<<ln;
        return;
    }
    if(mx > m){
        NA;
        return;
    }

    int l = 0 , r = T[n-1] - T[0];
    int ans = T[n-1] - T[0];
    while(l<=r){
        int mid = l + (r-l)/2;
        SegTree sg(n);
        vector<ll> dp(n+1);
        stack<int>st;
        int ptr = 0;
        for(int i = 0;i < n;i++){
            while(!st.empty() && C[i] >= C[st.top()]){
                int idx = st.top(); st.pop();
                int prv = st.empty() ? 0 : st.top()+1;
                sg.update(prv,idx,C[i]-C[idx]);
            }
            st.push(i);
            sg.update(i,i,C[i]);
            while(ptr < i && T[i]-T[ptr] > mid) ptr++;
            dp[i+1] = sg.query(ptr,i);
        }

        if(dp[n] <= m){
            ans = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
    }

    cout<<ans<<ln;

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