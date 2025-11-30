#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
#define ll long long
#define all(x) x.begin(),x.end()
#define ln "\n"
#define vi vector<ll>
#define pl pair<ll, ll>
#define vp vector<pl>

const int N = 5e5+10;
vector<pair<int,int>>adj[N];
int low[N],tin[N];
pair<bool,int> is_bridge[N];
int id[N]{};
int cnt[N]{};
int timer=0;
void init(int n,int m){
    for(int i=0;i<n;i++){
        adj[i].clear();
        low[i]=1e9;tin[i]=-1;
        cnt[i] = id[i] = 0;
    }
    for(int i=0;i<m;i++) is_bridge[i]= {false,0};
    timer=0;
}
int cur;
int comp;
int tarjan(int v,int p){
    low[v]=tin[v]=timer++;
    cnt[comp]++;
    int ret = 1;
    for(auto [u,e]:adj[v]){
        if(u==p)continue;
        id[e] = comp;
        if(tin[u]!=-1){
            low[v]=min(low[v],tin[u]);
            continue;
        }
        int x = tarjan(u,v);
        ret += x;
        low[v]=min(low[v],low[u]);
        if(low[u]>tin[v]){
            is_bridge[e] = {true , x};
        }   
    }
    return ret;
}

const int MOD = 1e9+7;
vector<int> splits_by_size[N];
void solve(){
    int n,m,c; cin>>n>>m>>c;
    init(n,m);
    for(int i=0; i<=n; i++) splits_by_size[i].clear();
    for(int i = 0 ;i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back({y,i});
        adj[y].push_back({x,i});
    }
    comp = 0;
    for(int i = 0; i < n ; i++){
        if(tin[i] == -1){
            cur = 0; comp++;
            tarjan(i,-1);
        }
    }
    bool valid = (comp > 1);
    for(int i = 0; i < m ; i++){
        valid |= is_bridge[i].first;
    }
    if(!valid){
        cout<<-1<<ln;
        return;
    }

    for(int i = 0; i < m; i++){
        if(is_bridge[i].first){
            int comp_id = id[i];
            int parent_size = cnt[comp_id];
            int cut_size = is_bridge[i].second;
            splits_by_size[parent_size].push_back(cut_size);
        }
    }

    ll sol = c * (comp - 1);
    ll mn = INT64_MAX;
    vi frq(n+1);
    for(int i = 1; i <= comp ; i++) frq[cnt[i]]++;
    vi bulk;
    for(int w = 1 ; w <= n ; w++){
        if(!frq[w]) continue;
        int cnt = frq[w];
        int singles = min(3ll,cnt);
        for(int x = 1 ; x <= singles ; x++) bulk.push_back(w);
        cnt -= singles;
        int pw = 1;
        while(cnt >= pw){
            bulk.push_back(pw*w);
            cnt -= pw;
            pw *=2;
        }
        if(cnt) bulk.push_back(cnt*w);
    }
    vi dp(n+1, 0);
    dp[0] = 1;
    for(auto w : bulk){
        for(int j = n ; j >= w ; j--) {
            dp[j] += dp[j-w];
            if(dp[j] >= MOD) dp[j] -= MOD;
        }
    }

    for(int j = 0 ;j  <= n ; j++) if(dp[j]){
        int l = j;
        int r = n - j;
        mn = min(mn , l*l + r*r);
    }

    for(int w = 1 ; w <= n ; w++){
        if(!frq[w]) continue;
        if(splits_by_size[w].empty()) continue;

        for(int j = w ; j <= n ; j++){
            dp[j] = dp[j] - dp[j-w];
            if(dp[j] < 0) dp[j] += MOD;
        }

        vi valid;
        for(int j = 0; j <= n ; j++) if(dp[j]) valid.push_back(j);
        
        for(auto cut : splits_by_size[w]){
            int tag = n/2 - cut;
            auto it = lower_bound(all(valid), tag);
            
            // Check value >= tag
            if(it != valid.end()){
                int l = *it + cut;
                int r = n - l;
                mn = min(mn , l*l + r*r);
            }
            
            // Check value < tag (closest smaller)
            if(it != valid.begin()){
                it = prev(it);
                int l = *it + cut;
                int r = n - l;
                mn = min(mn , l*l + r*r);                
            }
        }
    
        for(int j = n ; j >= w ; j--){
            dp[j] = dp[j] + dp[j-w]; 
            if(dp[j] >= MOD) dp[j] -= MOD;
        }
    }

    sol += mn;
    cout << sol << '\n';
}

signed main(){
    fast
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}