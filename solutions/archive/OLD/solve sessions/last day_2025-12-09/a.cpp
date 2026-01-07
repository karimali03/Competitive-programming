#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define vi vector<int>
#define int long long

void solve(int test_case) {
    int n, m; 
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    for(int i = 0; i < m; i++){
        int x, y; cin >> x >> y; x--, y--;
        g[x].push_back({y, i});
        g[y].push_back({x, i});
    }
    vi dep(n);
    vi par(n,-1);
    vi edg(n);
    int l,r;
    int mx = -1;
    int back;
    function<void(int,int)> dfs = [&](int x,int d = 1){
        dep[x] = d;
        for(auto &[it,idx] : g[x]){
            if(dep[it]){
                if(dep[it]+1 < dep[x] && mx < dep[it]){
                    mx = dep[it];
                    l = it , r = x;
                    back = idx;
                }
            }else{
                dfs(it,d+1);
                par[it] = x;
                edg[it] = idx;
            }
        }
    };

    dfs(0,1);

    vi cycle;
    cycle.push_back(back);
    for(int v = r ; v != l ; v = par[v]){
        cycle.push_back(edg[v]);
    }

    cout<<cycle.size()<<ln;
    for(auto &it : cycle) cout<<it+1<<" ";
    cout<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve(1);
    return 0;
}