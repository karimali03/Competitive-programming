#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ln "\n"
#define ll long long
#define ull unsigned long long
#define int  long long
#define vec vector
#define F first
#define S second
#define p pair
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i,a,b) for(int i=a;i<b;i++)
#define all(x)   x.begin(),x.end()
const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1};
const int dy[8]={1, -1, 0, 0, 1, -1, 1, -1};
const int mod = 998244353;

void setup(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
}


vi vis;
vii adj;
vi res;
void dfs(int node,int p){
  
    for(auto & x : adj[node]){
            if(p == x) continue;
            dfs(x,node);
            res[node]+=res[x];
 
    }
}
void solve() {
    int n; cin>>n;
    vis=vi(n);
    res=vi(n,1);
    adj=vii(n);
    for(int i=1;i<n;i++){
        int x; cin>>x;
        adj[x-1].push_back(i);
    }
    dfs(0,-1);
    for(auto it : res) cout<<it-1<<" ";
}
signed main() {
    setup();
  //  int t; cin>>t; while(t--)
        solve();   return 0;
}
