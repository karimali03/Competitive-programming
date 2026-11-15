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

    dsu(int n) :size(n, 1), par(n),cc(n) {
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
    int n,m; cin>>n>>m;
    vector<array<int,3>>g(m);
    for(int  i =0;i <  m; i++){
        int x,y,z; cin>>x>>y>>z;
        g[i] = {z+1 , x-1,y-1};
    }
    sort(rall(g));
    int res = 0;
    vii ad(n);
    vi color(n);
    dsu st(n);
    bool vld = true;
    vi cnt(3);
    function<void(int,int)> dfs = [&](int x,int c){
        cnt[c] += st.size[x];
        color[x] = c;
        for(auto &it : ad[x]){
            if(color[it] == 0) dfs(it,3-c);
            else if(color[it] == c) vld = false;
        } 
    };
    for(int i = 0;i < m ;){
        int t = g[i][0];
        int org = i;
        while(i < m && g[i][0] == t){
            int x = st.get(g[i][1]); int y = st.get(g[i][2]);
            ad[x].push_back(y);
            ad[y].push_back(x);
            i++;
        }
        for(int j = org ; j < i ; j++){
            cnt[1]  = cnt[2] = 0;
            int x = st.get(g[j][1]); 
            if(color[x] == 0){
                dfs(x,1);
                res += min(cnt[1],cnt[2]);
            } 
        }
        if(!vld){
            cout<<"impossible\n"; return;
        }
        for(int j = org ; j < i ; j++){
            int x = st.get(g[j][1]); int y = st.get(g[j][2]);
            color[x] = 0; color[y] = 0;
            ad[x].clear(); ad[y].clear();
        }
        cnt[1] = cnt[2] = 0;
        for(int j = org ; j < i ; j++){
            int x = st.get(g[j][1]); int y = st.get(g[j][2]);
            st.merge(x,y);
        }
    }

    cout<<"possible\n";
    cout<<res<<"\n";
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