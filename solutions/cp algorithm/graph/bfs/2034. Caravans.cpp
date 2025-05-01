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

int bfs(vii &v,int s , vi &vis , int mx = -1){
    queue<int>q;
    q.push(s);
    vis[s] = 1;
    int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto x = q.front(); q.pop();
            for(auto it : v[x]){
                if(!vis[it]){
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        if(mx != -1 && mx == lvl) break;
        lvl++;
    }
    while(!q.empty()){
        vis[q.front()] = 0; q.pop();
    }
    return lvl;
}
void solve(int test_case){
    int n,m; cin>>n>>m;
    vii v(n);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    int s,e,rs; cin>>s>>e>>rs; s--,e--,rs--;
    vi vis(n);
    int mx = bfs(v,rs,vis);
    int l = 0 , r = mx+1;
    int ans = mx;
    while( l <= r){
        int mid = l + (r-l)/2;
        vis = vi(n);
        bfs(v,rs,vis,mid);
        bool ok = (vis[s] || vis[e]);
        bfs(v,s,vis);
        ok = ok || (!vis[e]);
   
        if(ok){
            r = mid-1;
            ans = mid;
        }
        else{
            l = mid+1;
        }
    }
    cout<<ans;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}