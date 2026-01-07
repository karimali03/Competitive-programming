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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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







void solve(int test_case) {
    int n; cin>>n;
    vii adj(n);
    for(int i = 0 ; i < n-1;i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }   
    vector<int>par(n,-1);
    auto bfs = [&](int start) -> pair<int,int> {
        vector<int> dist(n, -1);
        queue<int> q;
        par = vi(n,-1);
        q.push(start);
        dist[start] = 0;
        int mx = 0;
        int node = start;
        while(!q.empty()){
            auto cur = q.front(); q.pop();
            for(auto x : adj[cur]){
                if(dist[x] == -1){
                    dist[x] = dist[cur] + 1;
                    par[x] = cur; 
                    if(dist[x] > mx){
                        mx = dist[x];
                        node = x;
                    }
                    q.push(x);
                }
            }
        }
        return {node,mx};
    };

  

    bool vld = true;
    for(int i  =0 ;i < n  ; i++) if(adj[i].size() > 2) vld = false;
    if(vld){
        NA; return;
    }

    auto [u, _] = bfs(0);
    auto [v, diameter] = bfs(u);

    vi path;
    int cur = v;
    while (cur != -1) {
        path.push_back(cur);
        cur = par[cur];
    }
    reverse(path.begin(), path.end());
    vi pre(n+1),suf(n+1);
    int prv = 0;
    for(int i = 1 ; i < (int)path.size()-1 ; i++){
        if(adj[path[i]].size() > 2){
            pre[i] = i - prv;
            prv = i; 
        }
        pre[i] += pre[i-1];
    }
    prv = (int)path.size()-1;
    for(int i = (int)path.size()-2 ; i >= 1 ; i--){
        if(adj[path[i]].size() > 2){
            suf[i] = prv - i;
            prv = i;
        }
        suf[i] += suf[i+1];
    }
    int mn = 1e12;
    for(int i = 0 ; i < (int)path.size()-1 ; i++){
            mn = min(mn , suf[i+1] + pre[i]);
    }
    for(int i = 1 ; i < (int)path.size() ; i++) mn = min(mn , pre[i-1]+suf[i]);
  
    for(int i = 1 ; i < (int)path.size()-1 ; i++){
        if(adj[path[i]].size() > 2){
            if(suf[i+1] + pre[i] == mn){
                int c = path[i-1]+1;
                int a = path[i+1]+1;
                int b = path[i]+1;
                cout<<a<<" "<<b<<" "<<c<<ln;
                return;
            }else if(pre[i-1] + suf[i] == mn){
                int c = path[i+1]+1;
                int a = path[i-1]+1;
                int b = path[i]+1;
                cout<<a<<" "<<b<<" "<<c<<ln;
                return;
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}