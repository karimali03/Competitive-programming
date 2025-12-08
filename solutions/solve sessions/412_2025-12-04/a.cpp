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


struct dsu {
    vector<int> sz, par;
    int cc;
    int res;

    dsu(int n) : cc(n), par(n) {
        res = 0;
        sz = vi(n);
    }

    void add(int x){
        sz[x] = 1;
        par[x] = x;
        res += ( sz[x] + 1)/2;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        par[x] = y;
        res = res - (sz[x] + 1)/2 - (sz[y] + 1)/2;
        sz[y] += sz[x];
        sz[x] = 0;
        res += (sz[y]+1)/2;
        cc--;
        return true;
    }

};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi ind(n); 
    iota(all(ind),0);
    vi res(n+1,1e10);
    sort(all(ind) , [&](int x,int y){
        return v[x] <= v[y];
    });
    dsu st(n);
    vi vis(n);
    for(int i = 0;i < n ; i++){
        int idx = ind[i];
        st.add(idx); 
        vis[idx] = 1;
        if(idx && vis[idx-1]) st.merge(idx-1,idx);
        if(idx+1 < n && vis[idx+1]) st.merge(idx,idx+1);
        res[st.res] = min(res[st.res] , v[idx]); 
    }
    for(int i = n-1 ; i > 0 ; i--) res[i] = min(res[i] , res[i+1]);
    for(int i=1;i<=n;i++){
        if(res[i] == 1e10) cout<<"-1 ";
        else cout<<res[i]<<" ";
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