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

vii adj;
void dfs(int x,int p , vi &dist){
    dist[x] = ( p == -1 ? 0 : dist[p]+1);
    for(auto it : adj[x]){
        if(it!=p){
            dfs(it,x,dist);
        }
    }
}

vi bfs(vi &d,int n,int mx){
    queue<int>q;
    vi dis(n,-1);
    f(i,0,n) if(d[i] == mx) q.push(i),dis[i]=0;
    int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while (sz--)
        {
            auto x = q.front(); q.pop();
            for(auto it : adj[x]){
                if(dis[it] == -1) dis[it] = lvl+1,q.push(it);
            }
        }
        lvl++;
    }
    return dis;
}



void solve(int test_case) {
    int n; cin>>n;   
    adj = vii(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vi d(n);
    dfs(0,-1,d);
    int idx = 0;
    int mx = *max_element(all(d));
    f(i,0,n) if(d[i] == mx) idx = i;
    d = vi(n);
    dfs(idx,-1,d);
    mx = *max_element(all(d));
    auto dis = bfs(d,n,mx);
    mx = *max_element(all(d));
    auto dis2 = bfs(dis,n,mx);
    f(i,0,n) dis[i] = max(dis[i],dis2[i]);
    vii dx(n);
    f(i,0,n) dx[dis[i]].push_back(i);
    vi res(n+1);
    for(int i = n ; i > mx ; i--) res[i] = n;
    int cnt = 0;
    vi vis(n);
    for(int i = mx ; i > 0 ; i--){
        for(auto it : dx[i]) if(!vis[it]) vis[it]=1,cnt++;
        res[i] = n - cnt+1;
    }
    for(int i = 1 ; i<=n;i++) cout<<res[i]<<" ";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}