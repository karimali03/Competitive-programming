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
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
}
 
/*
 think twice code once.
 BEFORE coding are you sure
 you understood the statement correctly?
 PLEASE do not forget to read the sample explanation carefully.
 TEST your idea or code on the corner cases.
 ANALYZE each idea you have thoroughly.
1. Think Greedy
2. Think Brute Force
3. Think solution in reverse order
4. Think DP [ check constraints carefully ]
5. Check base cases for DP and prove solution for Greedy
6. Think ->> Graph
*/
 
 
/*
 start with numbers sorted (  distinct values )
 else all possible variations
 start with numbers sorted
    from begin number can be used more than one
    from end number used one time only
 */
 
void solve() {
    int n; cin>>n;
   vi v(n);
   f(i,0,n) cin>>v[i];
   vi ans;
   ans.push_back(v[0]);
   for(int i=1;i<n;i++){
       int x= upper_bound(all(ans),v[i])-ans.begin();
       if(x==ans.size()) ans.push_back(v[i]);
       else ans[x]=v[i];
   }
   cout<<ans.size()<<ln;
}
 
 
signed main() {
    kemo();
    //  int t; cin>>t; while(t--)
    solve();
    return 0;
}