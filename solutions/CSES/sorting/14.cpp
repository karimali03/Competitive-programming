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
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
 
}
 
 
void solve() {
    int x,n; cin>>x>>n;
    set<int>st =  {0,x};
    multiset<int>mx; 
    mx.insert(x);
    f(i,0,n){
        int a; cin>>a;
        st.insert(a);
        auto bs = st.find(a);
        int prv = *prev(bs); 
        int nxt = *next(bs);
        mx.erase(mx.find(nxt-prv));
        mx.insert(nxt-a);
        mx.insert(a-prv);
        cout<<*mx.rbegin()<<" ";
    }
}
 
 
signed main() {
    kemo();
  //  int t; cin>>t; while(t--)
        solve();
    return 0;
}