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

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_ + 5;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    // idx is 1..n
    void add(int idx, ll val){ 
        while(idx <= n){
            bit[idx] = (bit[idx] + val);
            idx += idx & -idx;
        }
    }
    // sum 1..idx
    ll sumPrefix(int idx){ 
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1));
    }
    // for range update , point query
    // update [l,r] +x  -> add(l,x) , add(r+1,-x) 
    // get idx  -> sumPrefix(idx)
};

const int N = 500005;
int sz[N] , big[N];
vector<int>g[N];
int color[N];
// Global data structure (e.g., frequency array, max variables)
int freq[N]{}; 
Fenwick st(N);
// answer
vector<pair<int,int>>qu[N];
ll ans[N];
// preprocess the tree to compute sizes and identify big children 
void pre(int x,int p){
    sz[x] = 1;
    big[x] = -1;
    for(auto &y : g[x]) if(y != p){
        pre(y,x);
        sz[x] += sz[y];
        if( big[x] == -1 || sz[y] > sz[big[x]]) big[x] = y;
    }
}

void upd(int x,int d){
    int cl = color[x];
    if(freq[cl]) st.add(freq[cl],-1);
    freq[cl] += d;
    if(freq[cl]) st.add(freq[cl],1);
}

// add or remove the contribution of a subtree rooted at 'x' to the global data structure
void add(int x,int p,int d){
    upd(x,d);
    for(auto &it : g[x]) if(it != p){
        add(it,x,d);
    }
}

int n,m; 
void sack(int x,int p,int keep){
    // add and remove light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) sack(it,x,0);
    // add big child
    if(~big[x]) sack(big[x],x,1);
    // add myself
    upd(x,1);
    // add light nodes
    for(auto &it : g[x]) if(it != p && big[x] != it) add(it,x,1);
    // answer queries
    for(auto &[k,idx] : qu[x]){
         ans[idx] = st.sumRange(k,N);
    }
    // remove if required
    if(!keep) add(x,p,-1);
}



void solve(int test_case) {
    cin>>n>>m;
    for(int i =0 ;i < n ;i++){
         cin>>color[i];
    }
   for(int i = 1; i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
   }
   for(int i = 0 ; i < m ; i++){
        int x,y; cin>>x>>y; x--;
        qu[x].push_back({y,i});
   }
   pre(0,-1);
   sack(0,-1,1);
   f(i,0,m){
        cout<<ans[i]<<ln;
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