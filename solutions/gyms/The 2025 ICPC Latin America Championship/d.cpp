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


const int N = 1000005;
int par[N],val[N];
int virtual_node = 0;
void init(int n){
    for(int i = 0;i < n ; i++) par[i] = i;
    virtual_node = n;
}

int get(int x){
    if(x == par[x]) return x;
    return par[x] = get(par[x]);
}

vi adj[N];
int res[N],sz[N]{};

void dfs(int x){
    if(adj[x].empty()){
            sz[x] = 1;
            return;
    }
    for(auto it : adj[x]){
            dfs(it); 
            sz[x] += sz[it];
    }
}


void prop(int x,int ret){
    if(adj[x].empty()){
            res[x] = ret;
            return;
    }
    for(auto it : adj[x]){
            prop(it , ret + (sz[x]-sz[it]) * val[x] );
    }
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    for(int i = 0; i < n ; i++) cin>>val[i];
    vector<array<int,3>> edg(m);
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        edg[i] = {x,y,max(val[x],val[y])};
    }   
    sort(all(edg) , [](array<int,3> &a,array<int,3> &b){
        return a[2] < b[2];
    });
    init(n);
    for(int i = 0;i < m ; i++){
        auto [x,y,w] = edg[i];
        x = get(x) , y = get(y);
        if(x != y){
            par[virtual_node] = virtual_node;
            val[virtual_node] = w;
            adj[virtual_node].push_back(x);
            adj[virtual_node].push_back(y);
            par[x] = virtual_node , par[y] = virtual_node;
            virtual_node++;
        }
    }
    dfs(virtual_node-1);
    prop(virtual_node-1,0);
    for(int i =0;i < n ; i++) cout<< res[i] + val[i]<<" ";
    cout<<ln;
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