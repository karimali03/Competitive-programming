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

const int INF = 1e9+5;
struct SegmentTree {
    struct node {
        int mx,idx;
    };

    int n; // Padded size (power of 2)
    vector<node> tree;
    node neutral;
   

    // Constructor pads size to the next power of 2
    SegmentTree(int size)  {
        n = 1;
        while (n < size) n <<= 1;
        
        neutral = {-INF,-1};
        tree.assign(2 * n, neutral);
    }

    node merge(const node &a, const node &b) {
        if(a.mx > b.mx) return a;
        else return b;
    }

    // Build array in O(N)
    void build(const vector<int>& a) {
        // Place leaves
        for (int i = 0; i < (int)a.size(); i++) {
            tree[n + i] = {a[i],i};
        }
        // Build internal nodes bottom-up
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
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
    vi v(n); cin>>v;
    vi vv = v;
    for(auto &it : v) vv.push_back(it);
    auto ng = NGE(vv);
    SegmentTree st(n*2);
    st.build(vv);
    for(int i = 0;i < n ; i++){
        int res = 0;
        int cur = i;
        while(cur < i+n-1){
            if(ng[cur] > i+n-1) break;
            res += (ng[cur]-cur) * vv[cur];
            cur = ng[cur];
        }
      //  cout<<i<<" "<<cur<<" "<<res<<" "<<n+i-1<<ln;
        int l = cur, r = n+i-1;
        while(l<r){
             auto mx = st.query(l+1,r);
             res += (mx.idx-l) * mx.mx;
             l = mx.idx;
        }
        cout<<res<<" ";
    }
    cout<<ln;
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