#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define int long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
 




vector<vector<int>> build_adj(){
    int n,m; cin>>n>>m;
    vector<vector<int>> v(n,vi(n,1e9));
    f(i,0,n) v[i][i] = 0; // no self loops
    f(i,0,m){
        int a,b,cost; cin>>a>>b>>cost; a--,b--;
        v[a][b] = min(v[a][b],cost);
    }
    return v;
}

void flyod(vector<vector<int>> & v){
    int n = v.size();
    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n ;i++){
            for(int j = 0 ; j < n ; j++){
                int relax = v[i][k] + v[k][j];
                v[i][j] = min(v[i][j],relax);
            }
        }
    }
}



int main(){
    return 0;
}