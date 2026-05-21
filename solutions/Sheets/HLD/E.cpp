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
    Fenwick st(n);
    f(i,0,n) st.add(i+1,hld.val[i]); 
    int q; cin>>q;
    while(q--){
        int op; cin>>op;
        if(op == 2){
            int x,y; cin>>x>>y; x--,y--;
            auto rngs = hld.query(x,y);
            int res = 0;
            for(auto &[l,r] : rngs){
                res += st.sumRange(l+1,r+1);
            }
            cout<<res<<ln;
        }else{
            int x,it; cin>>x>>it; x--;
            st.add(hld.mp[x]+1,it - st.sumRange(hld.mp[x]+1,hld.mp[x]+1));
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