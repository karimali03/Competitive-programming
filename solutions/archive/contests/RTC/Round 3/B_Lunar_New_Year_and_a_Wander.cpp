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
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case){
    int n,m; cin>>n>>m;
    vii adj(n);
    for(int i = 0 ; i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y); adj[y].push_back(x);
    }   
    priority_queue<int,vi,greater<>>k;
    vi row; k.push(0); vi vis(n); vis[0] = 1;
    while(!k.empty()){
        auto x = k.top(); k.pop();
        row.push_back(x);
        for(auto it : adj[x]){
            if(!vis[it]) k.push(it);
            vis[it] = 1;  
        }
    }
    for(auto it : row) cout<<++it<<" ";

}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}