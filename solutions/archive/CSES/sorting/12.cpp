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
void setup(){
 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
 
}
 
 
void solve() {
    int n; cin>>n;
    vi v(n);
    f(i,0,n) cin>>v[i];
    set<int>st;
    int i=0,j=0;
    int mx=0;
    while(j<n){
        if(!st.count(v[j])){
            st.insert(v[j]);
            j++;
        }
        else{
            mx= max(mx,j-i);
            st.erase(v[i]);
            i++;
        }
    }
    mx=max(mx,j-i);
    cout<<mx<<ln;
}
 
 
signed main() {
    setup();
  //  int t; cin>>t; while(t--)
        solve();
    return 0;
}