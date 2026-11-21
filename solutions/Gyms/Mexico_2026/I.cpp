#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vii vector<vi>
#define all(X) X.begin(),X.end()
#define int ll 

const int N = 2e5+10;
void solve(){
    int n; cin>>n;
    vi a(n); for(int i=0;i<n;i++) cin>>a[i];
    vii g(n);
    vector<array<int,3>>v(n);
    for(int i=1;i<n;i++){
        int x,y; cin>>x>>y; x--,y--;
        char c; cin>>c;
        int z = 0;
        if(c == '<') z = 1;
        else if(c == '=') z = 2;
        v[i-1] = {x,y,z};
        if(z == 2){
            g[x].push_back(y); 
            g[y].push_back(x);
        }
    }
    vi id(n,-1);
    vii gr(n);
    int cur = 0;
    function<void(int)> dfs = [&](int x){
        id[x] = cur;
        gr[cur].push_back(x);
        for(auto &it : g[x]) if(id[it] == -1) dfs(it);
    };
    for(int i = 0;i < n ; i++){
        if(id[i] == -1){
            dfs(i); cur++;
        }
    }
    vii gg(n);
    for(int i = 0;i < n-1 ; i++){
        auto [x,y,z] = v[i];
        if(z == 2) continue;
        if(z == 1) gg[id[x]].push_back(id[y]);
        else gg[id[y]].push_back(id[x]);
    }
    for (int i = 0; i < gg.size(); i++)
    {
        sort(all(gg[i]));
        gg[i].erase(unique(all(gg[i])), gg[i].end());
    }
    
    vi in(n);
    for(int i  =0;i  < cur ; i++){
        for(auto &it : gg[i]) in[it]++;
    }
    queue<int>q; 
    for(int i = 0 ;i < cur ; i++) if(in[i] == 0) q.push(i);
    vi b(n, 1);
    vi V(gg.size()+10, 1);
     int val = 1;
    vector<int>ord;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto cur = q.front(); q.pop();
            ord.push_back(cur);
            for(auto &it : gg[cur]) if(--in[it] == 0) q.push(it);
            for(auto &X : gr[cur]) b[X] = val;
        }
        val++;
    }
    // reverse(all(ord));
    // for (int i = 0; i < ord.size(); i++)
    // {
    //     ll u = ord[i];
    //     for (auto it : gg[u]) V[it] = max(V[it], V[u]+1);
    //     for (auto x : gr[u]) b[x] = V[u];
    // }
    
    int ans = 0;
    for(int  i =0;i < n ; i++) ans += a[i] * b[i];
    cout<<ans<<"\n";
    for(int i = 0;i  < n ;i++) cout<<b[i]<<" ";
    cout<<"\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
