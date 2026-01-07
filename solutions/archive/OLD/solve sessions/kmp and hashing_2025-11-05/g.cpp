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

const int MOD = 1e9+7;
const int BASE = 37;
const int N = 100005;
ll POW[N];
ll Hash[10][N]{};

ll fp(ll x,ll y){
    ll res = 1;
    while(y > 0){
        if(y&1)  res = res * x % MOD;
        x = x * x % MOD;
        y>>=1;
    }
    return res;
}

void init(){
    POW[0] = 1;
    for(int i = 1 ; i < N ; i++){
        (POW[i] = POW[i-1] * BASE)%=MOD;
        for(int x = 1 ; x <= 10 ; x++){
            (Hash[x-1][i] = Hash[x-1][i-1] + x * POW[i])%=MOD; 
        }
    }
}
struct SegmentTree {
    struct node {
        ll val;
    };
    
    vector<node> tree;
    vector<int> lazy;
    node neutral = {0};
    int no_operation = 0;
    
    int n;
    int sz;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, neutral);
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b , int len) {
        return { (a.val + (b.val * POW[len])%MOD)%MOD };
    }

    void push(int v, int tl, int tr , int deg = 2) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            tree[v].val = {Hash[lazy[v]-1][tr-tl+1]};
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                    lazy[v * 2 + 1] = lazy[v];
                    lazy[v * 2 + 2] = lazy[v];
                }
            push(v * 2 + 1, tl, (tl + tr) / 2 , deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

    void build(string &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {Hash[a[tl]-'0'][1]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2] , tm-tl+1);
        }
    }
    
    void build(string &a){
        build(a,0,0,sz-1);
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right , max(0ll,min(r,tm)-l+1));
    }
    
    node query(int l,int r){
        return query(0,0,sz-1,l,r);
    }
    // set [l,r] to x
    void update(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
             lazy[v] = x;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), x);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2] , tm-tl+1);
        }
    }
    
    void update(int l,int r,int idx){
         update(0,0,sz-1,l,r,idx);
    }
};


void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    string s; cin>>s;
    int q = m + k;
    SegmentTree st(n);
    st.build(s);
    while(q--){
        int op; cin>>op;
        int l,r,x; cin>>l>>r>>x; l--,r--;
        if(op == 1){
            st.update(l,r,x+1);
        }else{
            auto a = st.query(l+x,r).val;
            auto b = st.query(l,r-x).val;
            if(a == b) YES;
            else NO;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}