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

void solve(int test_case) {
    int n; cin>>n;
    vii g(n); 
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int mx = 0;
    f(i,0,n) mx = max(mx , (int)g[i].size() + 1);
    vi color(n);
    vi vis(n);
    function<void(int,int)> dfs = [&](int x,int p){
        int cur = 0;
      //  cout<<x+1<<" : ";
     //   cout<<vis<<ln;
        for(auto &it : g[x]){
            if(it == p) continue;
            while(vis[cur]) cur = (cur+1)%mx;
            vis[cur] = 1;
            color[it] = cur;
       //     cout<<it+1<<" "<<x+1<<" "<<p+1<<" "<<color[it]<<" "<<color[x]<<" ";
        //    if(p != -1) cout<<color[p];
        //    cout<<ln;
        }
        for(auto &it : g[x]){
            if(it == p) continue;
            vis[color[it]] = 0;
        }
        if(p != -1) vis[color[p]] = 0;
        for(auto &it : g[x]){
            if(it == p) continue;
            vis[color[it]] = 1;
            dfs(it,x);
            vis[color[it]] = 0;
        }
        if(p != -1) vis[color[p]] = 1;
    };
    vis[0] = 1;
    color[0] = 0;
    dfs(0,-1);
    cout<<mx<<ln;
    for(auto &it : color) cout<<it+1<<" ";
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