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


struct TwoECC {
    vector<vector<int>> g;
    vector<int> low, tin, org;
    vector<pair<int,int>> bridges;
    stack<int> st;
    vector<vector<int>> TwoEdgeCC, tree;
    int timer, n;

    TwoECC(vector<vector<int>> &adj) : g(adj) {
        timer = 0;
        n = g.size();
        low = tin = org = vector<int>(n, -1);
        
        for(int i = 0; i < n; i++) {
            if(tin[i] == -1) dfs(i, -1);
        }

        // Build the Tree
        tree = vector<vector<int>>(n);
        for(int i = 0; i < n; i++) {
            for(auto &it : g[i]) {
                if(org[i] != org[it]) {
                    tree[org[i]].push_back(org[it]);
                }
            }
        }
    }

    void dfs(int v, int p) { 
        low[v] = tin[v] = timer++;
        st.push(v);
        bool skip_p = false; 
        for(auto u : g[v]) { 
            if(u == p && !skip_p) {
                skip_p = true;
                continue;
            }
            
            if(tin[u] != -1) { // back edge 
                low[v] = min(low[v], tin[u]);
            } else { // tree edge
                dfs(u, v); 
                low[v] = min(low[v], low[u]);
                if(low[u] > tin[v]) bridges.push_back({v, u});
            }
        }

        if(low[v] == tin[v]) {
            vector<int> comp;
            while(true) {
                int node = st.top();
                st.pop();
                comp.push_back(node);
                if(node == v) break;
            }
            
            int r = comp[0]; 
            for(auto &it : comp) org[it] = r;
            TwoEdgeCC.push_back(comp);
        }
    }
};


const int M = 1e9+7;

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % M;
        a = a * a % M;
        b>>=1;
    }

    return res;
}


void solve(int test_case) {
    int n,m; cin>>n>>m;
    vi v(n); cin>>v;
    bool vld = false;
    vii g(n);
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        if(x == y){
            vld = true; continue;
        }
        g[x].push_back(y);
        g[y].push_back(x);
    }    
    TwoECC st(g);
    vii comp(n);
    for(int i = 0;i < (int)st.TwoEdgeCC.size() ; i++){
        for(auto &it : st.TwoEdgeCC[i]){
            comp[st.org[it]].push_back(it);
        }
    }

    vi vis(n);
    vector<array<int,30>>dp(n);
    vi cnt(n);
    auto add = [&](int x,int id){
        cnt[id]++;
        for(int i = 0;i < 30 ; i++){
            if((v[x]>>i)&1){
                dp[id][i]++;
            }
        }   
    };
    vi cur;
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        cur.push_back(x);
        for(auto &it : comp[x]) add(it,x);
        for(auto &it : st.tree[x]){
            if(vis[it]) continue;
            dfs(it);
            cnt[x] += cnt[it];
            for(int i =0 ; i < 30 ; i++){
                dp[x][i] += dp[it][i];
            }
        }
    };
    auto conv = [&](int i){
        array<int,30> ret;
        for(int b = 0; b < 30 ; b++){
            int res = dp[i][b] * (cnt[i] -  dp[i][b]);
            ret[b] = res;
        }
        return ret;
    };

    auto compr = [&](array<int,30>&a,array<int,30>&b){
        for(int i = 0;i < 29 ; i++){
            a[i+1] += (a[i] / 2);
            a[i] = (a[i]&1);
            b[i+1] += (b[i] / 2);
            b[i] = (b[i]&1);
        }
        for(int i = 29 ; i >= 0 ; i--){
            if(a[i] < b[i]) return true;
            if(b[i] < a[i]) return false;
        }
        return true;
    };
    array<int,30> base;
    for(int i = 0;i < 30 ; i++) base[i] = 1e9;
    vector<array<int,30>> A , B;
    for(int i = 0;i < n ; i++){
        if(!vis[st.org[i]]){
            cur.clear();
            dfs(st.org[i]);
            A.push_back(conv(st.org[i]));
            B.push_back(base);
            for(int j = 1 ; j < (int)cur.size() ; j++){
                int idx = st.org[cur[j]];
                auto l = conv(idx);
                for(int b = 0; b < 30 ;b++){
                    int ot = dp[st.org[i]][b] - dp[idx][b];
                    int zt = cnt[st.org[i]] - cnt[idx] - ot;
                    l[b] += ot * zt;

                }
                if(!compr(B.back() , l)) B.back() = l;
            }
        }
    }
    int sz = A.size();
   
    vector<array<int,30>>pre(sz),suf(sz);
    for(int i = 0;i < sz ; i++){
        pre[i] = A[i];
        if(i){
            for(int b= 0 ;b  <30 ;b++)
            pre[i][b] += pre[i-1][b];
        }
    }
    for(int i = n-1 ; i >= 0 ;i--){
        suf[i] = A[i];
        if(i != n-1){
            for(int b =0;b < 30 ; b++){
                suf[i][b] += suf[i+1][b];
            }
        }
    }
    auto merge = [&](int i1,int i2){
        auto ret = array<int,30>{};
        if(i1 >= 0 && i1 < sz){
            for(int b = 0; b < 30 ; b++){
                ret[b] += A[i1][b];
            }
        }
        if(i2 >= 0 && i2 < sz){
            for(int b = 0; b < 30 ; b++){
                ret[b] += A[i2][b];
            }
        }
        return ret;
    };
    auto mrg = [&](array<int,30> &a,int i){
        for(int b =0; b<  30 ; b++){
            a[b] += B[i][b];
        }
    };
    auto ret = base;
    for(int i = 0;i < sz ; i++){
        auto cur = merge(i-1,i+1);
        mrg(cur,i);
        if(!compr(ret,cur)) ret = cur;
    }

    if(vld){
        if(!compr(ret,A.back())) ret = A.back();
    }            

    ll res = 0;
    for(int i = 0 ;i  < 30 ; i++){
        if(!ret[i]) continue;
        res += fp((1ll << i) , ret[i]);
        res %= M;
    }
    cout<<res<<ln;
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