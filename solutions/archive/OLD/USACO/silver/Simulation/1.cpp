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

    freopen("cowsignal.in","r",stdin);
    freopen("cowsignal.out","w",stdout);

        solve();
    return 0;
}


void solve() {
    int n,m,k; cin>>n>>m>>k;
    vec<vec<char>>v(n,vec<char>(m));
    f(i,0,n){
        f(j,0,m){
            cin>>v[i][j];
        }
    }



    vec<vec<char>>res(n*k,vec<char>(m*k));
    int ii = 0;
    for(int i = 0 ; i < n ; i++){
        vec<char>row(m*k);
        int jj = 0;
        for(int j = 0 ; j < m ; j++){
            for(int s = 0 ; s < k ; s++){
                row[jj++] = v[i][j];
            }
        }
        for(int s = 0; s < k ; s++){
            res[ii++] = row;
        }
    }

    for(int i = 0 ;i  < n*k ;i++){
        for(int j = 0 ; j < m*k ; j++ ){
            cout<<res[i][j];
        }
        cout<<"\n";
    }
}
 
 