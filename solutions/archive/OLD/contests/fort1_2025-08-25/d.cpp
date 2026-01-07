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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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
        while(!st.empty() && v[st.top()] < v[i]){ // > for NSE
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
    node neutral = {INT32_MIN,-1}; 
    bool type;
    int sz;

    SegmentTree(int size,bool type):type(type) {
        n = 1;
        sz = size;
        while (n < size) n <<= 1;
        if(type) neutral = {INT32_MIN,-1};
        else neutral = {INT32_MAX,-1};
        tree.resize(2 * n, neutral);
    }

   
    node merge(const node &a, const node &b) {
        if(type) return a.val > b.val ? a : b;
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

    // Query 2: Conditional query in [l, r] (e.g., find first index with value <= lf)
    // Returns index or INT32_MAX if not found
    pair<int,int> query_conditional(int l,int r,int lf,int v, int tl, int tr) {
        if (l > r || l > tr || r < tl) return {-1,-1}; // Out of segment
        if (tree[v].val <= lf) return {-1,-1}; // Condition not met in this segment
        if (tl == tr) return {tree[v].val,tl}; // Leaf node with condition met
        int tm = (tl + tr) / 2;
        auto rh_res = query_conditional(max(l, tm + 1), r, lf,v * 2 + 2, tm + 1, tr);
        if (rh_res.first != -1) return rh_res;
        return  query_conditional(l, min(r, tm), lf,v * 2 + 1, tl, tm);
    }

    pair<int,int> query_conditional(int l,int r,int lf){
        return query_conditional(l,r,lf,0,0,sz-1);
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
        return update(pos,new_val,0,0,sz-1);
    }

};


void solve(int test_case) {
    int n; cin>>n;
    vi v(n);
    vi pre(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin>>v[i-1];
        pre[i] = v[i-1] + pre[i-1];
    }
    auto ng = NGE(v);
    auto pg = PGE(v);
    SegmentTree mx(n+1,1),mn(n+1,0);
    mx.build(pre); mn.build(pre);
    for(int i = 0 ; i < n ; i++){
        int r = ng[i];
        int l = pg[i] + 2;
     
        auto ch1 = mx.query(l,r);
        auto ch2 = mn.query(l-1,ch1.idx-1);
        int res = ch1.val - ch2.val;
        ch1 = mn.query(l-1,r-1);
        ch2 = mx.query(ch1.idx+1,r);
        res = max(res , ch2.val - ch1.val);

        if(res > v[i]){
            NO;
            return;
        }
    }
    YES;
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