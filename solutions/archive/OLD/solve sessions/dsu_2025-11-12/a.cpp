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


struct LazyDsu{
    vector<int>par,lazy,sz,res;
    int cnt;
    LazyDsu(int n){
        cnt = n;
        par = lazy = sz = res = vi(2*n+1);
        for(int i = 0;i <= 2*n; i++){
            par[i] = i; sz[i] = 1;
        }
    };

    void apply(int v,int val){
        res[v]+=val; 
        lazy[v]+=val;
    }

    int get(int x){
        if(x == par[x]) return x;
        int p = get(par[x]);
        if(p != par[x]){
            apply(x,lazy[par[x]]);
        }
        return par[x] = p;
    }

    void add(int v,int val){
        apply(get(v),val);
    }

    int getVal(int x){
        int p = get(x);
        return res[x] + (x != par[x] ? lazy[p] : 0);
    }

    bool merge(int x,int y){
        x = get(x) , y = get(y);
        if(x == y) return false;
        int p = cnt++;
        par[x] = par[y] = p;
        lazy[p] = res[p] = 0;
        sz[p] = sz[x] + sz[y] ;
        return true;
    }
};
void solve(int test_case) {
    int n,m; cin>>n>>m;
    LazyDsu st(n);

    while(m--){
        string op; cin>>op;
        if(op == "join"){
            int x,y; cin>>x>>y; x--,y--;
            st.merge(x,y);
        }else if(op == "add"){
            int x,y; cin>>x>>y; x--;
            st.add(x,y);
        }else{
            int x; cin>>x; x--;
            cout<<st.getVal(x)<<ln;
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