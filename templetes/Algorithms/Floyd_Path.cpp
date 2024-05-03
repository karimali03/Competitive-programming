#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
 


vector<vector<int>>path;

vector<vector<int>> build_adj(){
    int n,m; cin>>n>>m;
    vector<vector<int>> v(n,vi(n,1e9));
    f(i,0,n) v[i][i] = 0; // no self loops
    f(i,0,m){
        int a,b,cost; cin>>a>>b>>cost;
        v[a][b] = min(v[a][b],cost);
    }
    return v;
}

void floyd(vector<vector<int>> & v){
    int n = v.size();
    path = vector<vector<int>>(n,vector<int>(n,-1));

    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n ;i++){
            for(int j = 0 ; j < n ; j++){
                int relax = v[i][k] + v[k][j];
                if(relax < v[i][j]){
                    v[i][j] =relax;
                    path[i][j] = k;
                }
               
            }
        }
    }
}

vector<int>v;
void build_path(int from,int to){
    if (path[from][to] == -1) { // direct edge
		if(v.empty() || v.back() != from) v.push_back(from);
        if(v.back() != to) v.push_back(to);
		return;
	}
	build_path(from, path[from][to]);
	build_path(path[from][to], to);
}



int main(){
   freopen("in.txt", "rt", stdin);

	vector<vector<int>> adjMatrix = build_adj();

	floyd(adjMatrix);

	build_path(0, 4);
    for(auto x : v) cout<<x<<" ";
    cout<<"\n";
	return 0;
}

/*
5 5
0 1 1
1 2 2
2 3 3
3 4 4
0 4 15


0 1 3 6 10
OO 0 2 5 9
OO OO 0 3 7
OO OO OO 0 4
OO OO OO OO 0
**************************
0 1 2 3 4

 */