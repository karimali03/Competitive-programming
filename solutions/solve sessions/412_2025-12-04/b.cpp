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

struct DSU {

    vector<int> sz, par, dif;
    int cc; 

    DSU(int n) : cc(n), sz(n, 1), par(n), dif(n, 0) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        int root = get(par[x]); 

        dif[x] = dif[x] ^ dif[par[x]]; 
        
        return par[x] = root;
    }
    // x y 1  diffrent set
    // x y 0 same set
    bool merge(int x, int y, int w = 0) {
        int rx = get(x), ry = get(y);

        if (rx == ry) {
            return ((dif[x] ^ dif[y]) == w);
        }

        int cost = dif[y] ^ dif[x] ^ w;

        if (sz[x] > sz[y]) {
            par[ry] = rx;
            dif[ry] = cost; 
            sz[rx] += sz[ry];
        } else {
            par[rx] = ry;
            dif[rx] = cost;
            sz[ry] += sz[rx];
        }
        cc--;
        return true;
    }
};

void solve(int tc){
    int n,m; cin>>n>>m;
    vector<array<int,3>> edg(m);
    for(int i = 0;i < m; i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        edg[i] = {w,x,y};
    }
    sort(rall(edg));
    DSU st(n);
    bool vld = true;
    vi res;
    for(int i = 0; i < m && vld; ){
        int j = i;
        while(j < m && edg[j][0] == edg[i][0]) j++;
     //  cout<<edg[i][0]<<ln;
        map<int,int>mp;
        set<pair<int,int>>s;
        int sz = 0;
        for(int x = i ; x < j ; x++){
            auto [w,a,b] = edg[x];
            int ra = st.get(a) , rb = st.get(b);
            if(ra != rb || st.dif[a] == st.dif[b]){
                int id1 = ra*2+st.dif[a];
                int id2 = rb*2+st.dif[b];
                if(s.count(minmax(id1,id2))) continue;
                s.insert(minmax(id1,id2));
                mp[id1]++; mp[id2]++; 
                sz++;
            }
        }

        bool cn = false;
        for(int x = i ; x < j ; x++){
            auto [w,a,b] = edg[x];
            int ra = st.get(a) , rb = st.get(b);
            if(ra != rb || st.dif[a] == st.dif[b]){
                int id1 = ra*2+st.dif[a];
                int id2 = rb*2+st.dif[b];
                int c1 = mp[id1];
                int c2 = mp[id2];
                int rem = sz - c1 - c2 + 1;
                if(id1 == id2) rem = sz - c1 - c2 + 3;
              ///  cout<<id1<<" "<<id2<<" "<<c1<<" "<<c2<<" "<<sz<<" "<<rem<<ln;
                if(rem > 0) cn = true; 
            }
           // cout<<"-------\n";
        }
        if(cn) res.push_back(edg[i][0]);
        for(int x = i ; x < j ; x++){
            if(!st.merge(edg[x][1],edg[x][2],1)) vld = false;
        } 
        i = j;
    }
    if(vld) res.push_back(0);
    if(res.empty()) cout<<"IMPOSSIBLE\n";
    else{
        reverse(all(res));
        for(auto &it : res) cout<<it<<"\n";
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