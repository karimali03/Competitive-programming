#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ln "\n"
#define ll long long
#define int long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i,a,b) for(int i=a;i<b;i++)
#define all(x)   x.begin(),x.end()
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
 
const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1};
const int dy[8]={1, -1, 0, 0, 1, -1, 1, -1};
const int mod = 1000000007;
void kemo(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
 

void solve(); 

signed main() {
    kemo();
  //  int t; cin>>t; while(t--)

   freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);

        solve();
    return 0;
}


void solve() {
    int n,m; cin>>n>>m;
    map<int,int>mp1,mp2;
    int cur1 = 0 , cur2 = 0;
    for(int i = 0 ; i < n ; i++){
        int x,y; cin>>x>>y;
        mp1[x] = y;
    }
    for(int i = 0 ; i < n ; i++){

    }
}
 
 