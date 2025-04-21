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

int edge = 0;
vii adj;
int dfs(int u , int p){
    int cnt = 1;
    for(auto v : adj[u]){
        if(v == p) continue;
        int x = dfs(v,u);
        if(!x) edge++;
        cnt+=x;
    }
    return (cnt&1?cnt:0);
}
void solve(int test_case){
    int n; cin>>n;
    adj = vii(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y); adj[y].push_back(x);
    }   
    int res = dfs(0,-1);
    if(res) cout<<-1<<ln;
    else cout<<edge<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}