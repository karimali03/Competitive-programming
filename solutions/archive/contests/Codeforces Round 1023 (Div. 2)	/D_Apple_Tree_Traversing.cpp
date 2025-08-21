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
#define YES cout<<"Yes\n"
#define NO cout<<"No\n";
#define INF 1e18
#define int long long
#define uni(v) v.erase(unique(all(v)), v.end())
#define pp(x) push_back(x)
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


int n;
vii adj;
vi vis;
set<int>nodes;
vi par;

pair<int,int> bfs(int st,int en = -1){
    map<int,int>dist;
    int node = st;
    queue<int>q; 
    q.push(st); 
    dist[st] = 1;
    int dis = 1;
    while(!q.empty()){
        auto x = q.front(); q.pop();
        if(x == en) break;
        for(auto it : adj[x]){
            if(!vis[it] && !dist.count(it)){
                dist[it] = 1 + dist[x];
                q.push(it);
                if(dist[it] > dis) dis=dist[it],node=it;
                else if(dist[it] == dis && it > node) node=it;
                if(en != -1) par[it] = x;
            }
        }
    }
    return {node,dis};
}

void calc(int node,vii&res){
    auto t1 = bfs(node);
    auto t2 = bfs(t1.first);
    auto t3 = bfs(t1.first,t2.first);
    res.push_back({t2.second,max(t1.first,t2.first),min(t1.first,t2.first)});

    debug(t1);
    debug(t2);
    debug(t3);
    int x = t2.first;
    while (x != -1)
    {
        vis[x] = 1;
        nodes.erase(x);
        x = par[x];
    }
    debug(vis);
}

void solve(int test_case) {
    int n; cin>>n;
    vii res;
    par = vi(n,-1);
    adj = vii(n);
    vis = vi(n);
    f(i,0,n) nodes.insert(i);
    for(int i = 0 ,u,v ; i < n-1 ; i++){
        cin>>u>>v; v--,u--;
        adj[u].pp(v);
        adj[v].pp(u);
    }   

    while(!nodes.empty()){
        calc(*nodes.begin(),res);
    }
    sort(rall(res));
    for(auto it : res) cout<<it[0]<<" "<<it[1]+1<<" "<<it[2]+1<<" ";
    cout<<ln;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}