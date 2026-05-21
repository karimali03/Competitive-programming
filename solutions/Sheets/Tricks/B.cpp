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
    vector<int> size, par;
    int cc;

    dsu(int n) : cc(n), size(n, 1), par(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

};
void solve(int test_case) {
    int n,m,q; cin>>n>>m>>q;
    vector<pair<int,int>>v(m);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        v[i] = {x,y};
    }
    vector<pair<int,int>>query(q);
    f(i,0,q){
        int x,y; cin>>x>>y; x--,y--;
        query[i] = {x,y};
    }
    
  
    vi L(q),R(q),ans(q,-1);
    vii buckets(m);
    f(i,0,q){
        if(query[i].first == query[i].second){
            ans[i] = 0;
            L[i] = 10;
        }else L[i] = 0,R[i] = m-1;
    } 
    auto update = [&]() -> bool{
        bool vld =  false;
        for(int i =0 ;i < q ; i++){
            if(L[i] <= R[i]){
                buckets[(L[i]+R[i])/2].push_back(i);
                vld = true;
            }
        }
        return vld;
    };

    while(update()){
        dsu st(n);
        for(int mid = 0; mid < m ; mid++){
            st.merge(v[mid].first,v[mid].second);
            for(auto &idx : buckets[mid]){
                auto [a,b] = query[idx];
                if(st.get(a) == st.get(b)){
                    ans[idx] = mid+1;
                    R[idx] = mid-1;
                }else L[idx] = mid+1;
            }
            buckets[mid].clear();
        }
    }
    f(i,0,q) cout<<ans[i]<<ln;
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