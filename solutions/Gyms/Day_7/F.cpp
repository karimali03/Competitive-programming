#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vii vector<vi>
#define all(X) X.begin(),X.end()
#define ln "\n"
void solve(){
    int n,m; cin>>n>>m;
    vi v(n);
    vi id(n);
    for(int i =0 ;i < n ; i++){
        cin>>v[i];
        id[v[i]] = i;
    }
    vii g(n);
    for(int i = 0 ;i < m;  i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
    }

    vi vis(n);
    vi path;
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto &it : g[x]) if(!vis[it]) dfs(it);
        path.push_back(x);
    };
    for(int i=0;i<n;i++) if(!vis[i]) dfs(i);
    reverse(all(path));
  
    auto can = [&](int x){
        vi dp(n);
        int tag = 0;
        for(auto &it : path){
            dp[it] += (v[it] < x);
            tag = max(tag , dp[it]);
            for(auto &ch : g[it]){
                dp[ch] = max(dp[ch] , dp[it] );
            }
        }
        return tag == x;
    };
    int ans = 0;
    int l = 1,r = n;
    while(l<=r){
        int m = (l+r)/2;
        if(can(m)){
            ans = m;
            l = m+1;
        }else r = m-1;
    }
    cout<<ans<<ln;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    cin>>t;
    while(t--) solve();
    return 0;
}