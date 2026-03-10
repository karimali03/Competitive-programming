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

const int MOD = 1e9+7;
const int N = 10000005;
vector<int>spf(N+5);   
void SPF(){   //  O(n*log(log(n)))
    for(int i=1;i<=N;i++) spf[i]=i;

     for(int i=2; i*i<=N; i++)
    {
        if(spf[i]==i)
           for(int j=i*i; j<=N; j+=i)
               if(spf[j]==j)   spf[j]=i;
    }
 }

ll fp(ll a,ll b){
    ll res=1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b>>=1;
    }

    return res;
}

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_;
        bit.assign(n+1, 1); // 1-indexed, supports indices 1..n
    }
    void add(int idx, ll val){ // idx is 1..n
        while(idx <= n){
            bit[idx] = (bit[idx] * val) % MOD;
            idx += idx & -idx;
        }
    }
    ll sumPrefix(int idx){ // sum 1..idx
        ll res = 1;
        while(idx > 0){
            res = (res * bit[idx]) % MOD;
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) * fp(sumPrefix(l-1),MOD-2)) % MOD;
    }
};


struct SegmentTree {
    struct node {
        int val;
        ll prd;
    };
    
    vector<node> tree;
    vector<pair<int,ll>> lazy;
    node neutral = {INT32_MAX,1};
    pair<int,ll> no_operation = make_pair(INT32_MAX,1);
    
    int n;
    int sz;

    SegmentTree(int size) {
        sz = size;
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n, {INT32_MAX,1});
        lazy.resize(2 * n, no_operation);
    }

    node merge(const node &a, const node &b) {
        return { min(a.val,b.val) , (a.prd*b.prd)%MOD };
    }

    void push(int v, int tl, int tr , int deg = 2) {
        if(deg == 0) return;
        if (lazy[v] != no_operation) { // if there is a pending operation
            
            (tree[v].prd *= fp(lazy[v].second,tr-tl+1))%=MOD;
            tree[v].val = min(tree[v].val , lazy[v].first);
        }
        if (tl != tr) {
            if(lazy[v] != no_operation) { // propagate the lazy value to children
                    (lazy[v*2+1].second *= lazy[v].second)%=MOD;
                    (lazy[v*2+2].second *= lazy[v].second)%=MOD;
                    lazy[v * 2 + 1].first = min(lazy[v*2+1].first,lazy[v].first);
                    lazy[v * 2 + 2].first = min(lazy[v*2+2].first,lazy[v].first);
            }
            push(v * 2 + 1, tl, (tl + tr) / 2 , deg-1); 
            push(v * 2 + 2, (tl + tr) / 2 + 1, tr , deg-1);
        }
        lazy[v] = no_operation;
    }

    void build(vector<int> &a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) tree[v] = {spf[a[tl]],a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2 + 1, tl, tm);
            build(a, v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void build(vector<int> &a){
        build(a,0,0,sz-1);
    }

    node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r) return neutral;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return merge(left, right);
    }
    
    node query(int l,int r){
        return query(0,0,sz-1,l,r);
    }
    // set [l,r] to x
    void update(int v, int tl, int tr, int l, int r, int x) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v].first = min(lazy[v].first,spf[x]);
            (lazy[v].second *= x)%=MOD;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(v * 2 + 1, tl, tm, l, min(r, tm), x);
            update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, x);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    
    void update(int l,int r,int idx){
         update(0,0,sz-1,l,r,idx);
    }
};


void solve(int test_case) {
    int n,q; cin>>n>>q;
    SegmentTree st(n);
    vi v(n); cin>>v;
    st.build(v);
    while(q--){
        int op; cin>>op;
        if(op == 1){
            int l,r; cin>>l>>r; l--,r--;
            auto ret = st.query(l,r);
            ll cur = ret.prd;
            (cur *= fp(ret.val,MOD-2))%=MOD;
            cout<<cur<<ln;
        }else{
            int l,r,x; cin>>l>>r>>x; l--,r--;
          //  cout<<op<<" "<<l<<" "<<r<<" "<<x<<endl;
            st.update(l,r,x);
         //   cout<<"--- "<<st.query(l,r).val<<ln;
         //   cout<<"-- "<<st.query(l,r).prd<<ln;
        }
       
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SPF();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
         solve(i);
    }

    return 0;
}