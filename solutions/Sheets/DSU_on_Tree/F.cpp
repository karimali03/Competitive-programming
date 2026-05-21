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

const int N = 200005;
int sz[N],big[N],dep[N];
vector<int> g[N];
int color[N];
map<int,int> st[N];
vector<pair<int,int>> qu[N];
int ans[N];
void pre(int u,int d){
    sz[u] = 1;
    big[u] = -1;
    dep[u] = d;
    for(auto &it : g[u]){
        pre(it,d+1);
        sz[u] += sz[it];
        if(big[u] == -1 || sz[it] > sz[big[u]]) big[u] = it;
    }
}

void upd(int x,int d){
    int h = dep[x];
    st[h][color[x]] += d;
    if(st[h][color[x]] == 0) st[h].erase(color[x]);
}

void add(int x,int d){
    upd(x,d);
    for(auto &it : g[x]) add(it,d);
}

void sack(int x,int keep){
    for(auto &it : g[x]) if(it != big[x]) sack(it,0);
    if(~big[x]) sack(big[x],1);
    upd(x,1);
    for(auto &it : g[x]) if(it != big[x]) add(it,1);
    // answer queires
    for(auto &[a,idx] : qu[x]){
        ans[idx] = st[a+dep[x]].size();
    }
    if(!keep) add(x,-1);
}
void solve(int test_case) {
    int n; cin>>n;
    vector<string>v(n);
    vector<string> val(n);
    vi root;
    for(int i= 0 ;i < n;i++){
        string s; cin>>s;
        v[i] = val[i] = s;
        int p; cin>>p; p--;
        if(p != -1) g[p].push_back(i);
        else root.push_back(i);
    }
    sort(all(val));
    val.erase(unique(all(val)),val.end());
    for(int i = 0;i < n ; i++){
        color[i] = lower_bound(all(val),v[i]) - val.begin() + 1;
    }
    int m; cin>>m;
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y; x--;
        qu[x].push_back({y,i});
    }
    for(auto &it : root){
        pre(it,1);
        sack(it,0);
    }
    for(int i =0 ;i < m ; i++) cout<<ans[i]<<ln;
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