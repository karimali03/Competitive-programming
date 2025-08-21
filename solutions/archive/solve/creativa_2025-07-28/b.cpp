#include "bits/stdc++.h"
#define ll long long
#define pl pair<ll, ll>
#define vi vector<ll>
#define vii vector<vi>
#define all(X) X.begin(), X.end()
using namespace std;
#define int ll


vi calc(int n,int src,vii &g){
    queue<int>q;
    vi lvl(n,-1);
    q.push(src); lvl[src]=0;
    while(!q.empty()){
         auto x = q.front(); q.pop();
         for(auto it : g[x]){
             if(lvl[it] == -1){
                 lvl[it] = 1+lvl[x];
                 q.push(it);
             }
         }
    }
    return lvl;
}



void solve() {
   int n,m,k; cin>>n>>m>>k;
   vii g(n);
   for(int i = 0 ; i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
   }
   vi nodes(k);
   vector<bool> rm(n);
   for(int i = 0 ; i < k ; i++) {
       cin>>nodes[i];
       nodes[i]--;
       rm[nodes[i]] = true;
   }

   vii g2(n),up(n);
   auto d1 = calc(n,0,g);
   auto d2 = calc(n,n-1,g);
   vector<set<int>> lvl(d1[n-1]+1);
   vector<bool>reach(n);
   vector<int>rnk1(n),rnk2(n);
   for(int i = 0 ; i < n ; i++){
       if(d1[i] + d2[i] == d1[n-1]){
           reach[i] = true;
           lvl[d1[i]].insert(i);
           for(auto it : g[i]){
               if(d1[it] > d1[i] && (d1[it]+d2[it] == d1[n-1])){
                   g2[i].push_back(it);
                   rnk1[i]++;
                   rnk2[it]++;
                   up[it].push_back(i);
                }
            }
        }
    }
    int cr = 0;
    for(int i = 1 ; i < d1[n-1];  i++){
        if(lvl[i].size() == 1) cr++;
    }
    cout<<cr<<" ";

    function<void(int)> er = [&](int x) {
        if(!reach[x] || cr == -1) return;
        reach[x] = false;
        lvl[d1[x]].erase(x);
        if(lvl[d1[x]].size() == 1) cr++;
        else if(lvl[d1[x]].empty()) cr = -1;
        for(auto it : up[x]){
            if(it == 0) continue;
            rnk1[it]--;
            if(rnk1[it] == 0) er(it);
        }
        for(auto it : g2[x]){
            if(it == n-1) continue;
            rnk2[it]--;
            if(rnk2[it] == 0) er(it);
        }
    };
    for(auto it : nodes){
        if(!reach[it] || cr == -1){
            cout<<cr<<" ";
            continue;
        }
        er(it);
        cout<<cr<<" ";
    }
    cout<<"\n";

}

signed main() {
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }   
}