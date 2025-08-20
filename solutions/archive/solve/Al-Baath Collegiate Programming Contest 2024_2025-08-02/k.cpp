#include "bits/stdc++.h"

#define int ll
#define ll long long
#define pl pair<ll, ll>
#define vi vector<ll>
#define vii vector<vi>
#define all(X) X.begin(), X.end()
#define sortx(X) sort(all(X))
using namespace std;
#define ln "\n"

const int N = 5e4+10; 
vector<int> adj[N],g[N];
int tin[N],low[N],timer;
int comp[N],comp_cnt;
stack<int>st;
bool on_stack[N];

void init(int n) {
    for(int i=0;i<n;i++){
        adj[i].clear();
        tin[i]=low[i]=-1;
        comp[i]=-1;
        g[i].clear();
        on_stack[i]=false;
    }
    while(!st.empty())st.pop();
    timer=comp_cnt=0;
}
void dfs(int v){
    tin[v]=low[v]=timer++;
    st.push(v);
    on_stack[v]=true;

    for(int u:adj[v]){
        if(tin[u]==-1){
            dfs(u);
            low[v]=min(low[v],low[u]);
        } else if(on_stack[u]){
            low[v]=min(low[v],low[u]);
        }
    }

    if(low[v]==tin[v]){
        while(true){
            int u=st.top();st.pop();
            comp[u]=comp_cnt;
            on_stack[u]=false;
            if(u==v)break;
        }
        comp_cnt++;
    }
}

int vis[N];
void topo(int v,vi &path){
    vis[v] = 1;
    for(auto it : g[v]){
        if(!vis[it]) topo(it,path);
    }
    path.push_back(v);
} 


bitset<N> dp1[N],dp2[N];

void solve() {
  int n,m; cin>>n>>m;
  init(n);
  vector<pair<int,int>>edg(m);
  for(int i =0 ; i < m ; i++){
    int x,y; cin>>x>>y; x--,y--;
    adj[x].push_back(y);
    edg[i] = {x,y};
  }
  for(int i =0 ; i < n ; i++) if(tin[i] == -1) dfs(i);
  vi cnt(comp_cnt);
  for(int i = 0 ;i  < m ; i++){
        auto[x,y] = edg[i];
        if(comp[x] != comp[y]){
            g[comp[x]].push_back(comp[y]);
            cnt[comp[y]]++;
        } 
  }
  fill(vis,vis+comp_cnt,0);
  vi path;
  for(int i = 0 ;i  < comp_cnt ; i++) if(cnt[i] == 0) topo(i,path);
    int q; cin>>q;
    set<int>st,en;
    while(q--){
        int x,y; cin>>x>>y; x--,y--;
        st.insert(comp[x]);
        en.insert(comp[y]);
    } 
    for(int i = 0 ;i < comp_cnt ; i++){
        dp1[i] = dp2[i] = 0;
    }
    for(auto it : en){
        dp2[it].set(it);
    }
    for(auto it : path){
        for(auto x : g[it]){
            dp2[it]|=dp2[x];
        }
    }
    reverse(all(path));
    for(auto it : st) dp1[it].set(it);
    for(auto it : path){
        for(auto x : g[it]){
            dp1[x]|=dp1[it];
        }
    }
    for(int i = 0 ; i < comp_cnt ; i++){
         if(dp1[i].count() == st.size() && dp2[i].count() == en.size()){
            cout<<"YES\n";
            return;
         }
    }
    cout<<"NO\n";

}

signed main() {
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    
    cin >> t;
    while (t--)
    {
        solve();
    }
}