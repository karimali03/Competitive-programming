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


#define Y return void(cout<<"Y\n")
#define N return void(cout<<"N\n")
void solve(int test_case) {
    int n; cin>>n;
    int l; cin>>l;
    vi L(l); cin>>L;
    int r; cin>>r;
    vi R(r); cin>>R;
    vii g(n+1,vi(n+1));
    for(int i = 0;i < l-1 ; i++){
        auto x = minmax(L[i],L[i+1]);
        g[x.first][x.second]++;
    }   
    for(int i = 0 ; i < r-1 ; i++){
        auto x = minmax(R[i],R[i+1]);
        g[x.first][x.second]++;
    }
    int cnt = 0;
    pair<int,int> miss = { -1 , -1};
    for(int i = 1;i <= n ; i++){
        for(int j = i+1 ; j <= n ;j++){
            if(g[i][j] > 1) N;
            if(!g[i][j]){
                cnt++;
                miss = {i , j};
            }
        }
    }
    for(int i = 1 ; i <= n ; i++) if(g[i][i]) N;
    if(cnt == 0){
        if(l && r) N;
        Y;
    }
    if(cnt == 1){
        if(l && r){
            auto x = minmax(L.back(),R[0]);
            if(x.first == miss.first && x.second == miss.second) Y;
            N;
        }
        else if(l){
            if(L.back() == miss.first || L.back() == miss.second) Y;
            N;
        }else if(r){
            if(R[0] == miss.first || R[0] == miss.second) Y;
            N;
        }
        Y;
    }
   // cout<<cnt<<ln;
    vii adj(n+1);
    vi vis(n+1,1);
    for(int i = 1;i <= n ; i++){
        for(int j = i+1 ; j <= n ;j++){
            if(!g[i][j]){
                adj[i].push_back(j);
                adj[j].push_back(i);
                vis[i] = vis[j] = 0;
            }
        }
    }
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto it : adj[x]) if(!vis[it]) dfs(it);
    };
    for(int i = 1; i <= n ; i++){
        if(!vis[i]){
            dfs(i);
            break;
        }
    }
    for(int i = 1; i <= n ; i++){
        if(!vis[i]){
            N;
        }
    }

    vi od;
    for(int i = 1 ; i <= n ; i++) if((int)adj[i].size()%2) od.push_back(i);
    if(l && adj[L.back()].empty()) N;
    if(r && adj[R[0]].empty()) N;
    if(od.empty()){
        if(l && r && L.back() != R[0]) N;
        Y;
    }
    if(od.size() != 2) N;
    if(l && L.back() != od[0] && L.back() != od[1]) N;
    if(r && R[0] != od[0] && R[0] != od[1]) N;
    if(l && r && L.back() == R[0]) N;
    Y;
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