#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

bool topo_sort(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> vis(n, 0); 
    vector<int> ordering;
    bool cycle = false;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1; 
        for (int v : adj[u]) {
            if (vis[v] == 1) {
                cycle = true; 
            } else if (vis[v] == 0) {
                dfs(v);
            }
            if (cycle) return;
        }
        vis[u] = 2; 
        ordering.push_back(u);
    };

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            if (cycle) return false;
        }
    }
    
    return true;
}

void solve() {
    int n; cin>>n;
    string s; cin>>s;

    if(n == 1){
        YES; return;
    }
    if(n == 2){
        if(s[0] == s[1]) YES;
        else NO;
        return;
    }
    
    vii g1(n), g2(n),g3(n);
    bool v1 = true, v2 = true;


    for(int i = 0; i < n; i += 2) {
        bool lf = (i == 0) || (s[i-1] == s[i]);
        bool rh = (i == n-1) || (s[i+1] == s[i]);
        if(!lf) {
            if(i-2 >= 0) g1[i-2].push_back(i);
            else v1 = 0;
        } 
        if(!rh) {
            if(i+2 < n) g1[i+2].push_back(i);
            else v1 = 0;
        } 
    }

    for(int i = 1; i < n; i += 2) {
        bool lf = (i == 0) || (s[i-1] == s[i]);
        bool rh = (i == n-1) || (s[i+1] == s[i]);
        if(!lf) {
            if(i-2 >= 0) g2[i-2].push_back(i);
            else v2 = 0;
        } 
        if(!rh) {
            if(i+2 < n) g2[i+2].push_back(i);
            else v2 = 0;
        } 
    }
 
   
    bool res = false;
    if(v1) res |= topo_sort(g1);
    if(v2) res |= topo_sort(g2);
    
    if(res) YES;
    else NO;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) solve();
  
    return 0;
}