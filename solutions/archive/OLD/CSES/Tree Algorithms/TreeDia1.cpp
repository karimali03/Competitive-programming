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
 
 
 
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
 
 
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
 
// Overload for set
template<typename T = int>
ostream &operator<<(ostream &out, const set<T> &s) {
    for (const T &x : s) out << x << ' ';
    return out;
}
 
// Overload for map
template<typename K = int, typename V = int>
ostream &operator<<(ostream &out, const map<K, V> &m) { 
    for (const auto &[key, value] : m) out << '(' << key << ": " << value << ") ";
    return out;
}
 
// Overload for pair
template<typename A = int, typename B = int>
ostream &operator<<(ostream &out, const pair<A, B> &p) {
    return out << p.first << ", " << p.second;
}
 
 
 
void kemo() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
}
 
 
 
void solve(int test_case);
 
signed main() {
    kemo();
 
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
 
    return 0;
}
 
vii adj;
vi depth;
vi dist;
int dfs(int node, int p) {
    int cnt = 0;
    for(auto x : adj[node]){
        if(x == p) continue;
        cnt = max(cnt, dfs(x,node));
    }
 
    return depth[node] = 1 + cnt;
}
 
int dfs2(int node, int p) {
    int mx1 = 0 , mx2 = 0;
    int mx1i = -1 , mx2i = -1;
    for(auto x : adj[node]){
        if(x == p) continue;
        if(depth[x] > mx1){
            mx2 = mx1 , mx2i = mx1i;
            mx1 = depth[x] , mx1i = x;
        }
        else if(depth[x] > mx2) mx2=depth[x],mx2i = x;
    }
 
    for(auto x : adj[node]){
        if(x == p) continue;
        if(x == mx1i){
            dist[x] = mx2 + 2;
        }
        else{
            dist[x] = mx1 + 2;
        }
        dist[x] = max(dist[x] , 1 + dist[node]);
        dfs2(x,node);
    }
 
    return dist[node] = max(dist[node] , 1 + mx1);
}
 
void solve(int test_case){
    int n; cin>>n;
    adj = vii(n);
    dist = depth = vi(n);
  
    for(int i = 0 ; i  < n-1 ; i++){
        int a,b; cin>>a>>b; a--,b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
     
    dfs(0,-1);
    dfs2(0,-1);
    for(auto x : dist){
        cout<<x-1<<" ";
    }
}