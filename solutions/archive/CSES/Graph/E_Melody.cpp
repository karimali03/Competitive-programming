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

vi vis;
vec<vec<pair<int,int>>>adj;
vi path;
void dfs(int u){
    while(!adj[u].empty()){
        auto [v,id] = adj[u].back();
        adj[u].pop_back();
        if(vis[id]) continue;
        vis[id]=  1;
        dfs(v);
    }
    path.push_back(u);
}

void solve(int test_case) {
    // v p v p v p 
    int n; cin>>n;
    path.clear();
    vis = vi(n);
    vi xx,yy;
    vec<pair<int,int>>edges(n);
    
    f(i,0,n){
        int x,y; cin>>x>>y; 
        edges[i] = {x,y};
        xx.push_back(x);
        yy.push_back(y);
    }
    sort(all(xx)); sort(all(yy));
    map<int,int>idx,idy;
    xx.erase(unique(all(xx)), xx.end());
    yy.erase(unique(all(yy)), yy.end());
    f(i,0,xx.size()) idx[xx[i]] = i;
    f(i,0,yy.size()) idy[yy[i]] = i+xx.size();
    map<pair<int,int>,int>mp;
    int sz = xx.size()+yy.size();
    adj = vec<vec<pair<int,int>>>(sz);
    f(i,0,n){
        mp[{idx[edges[i].first],idy[edges[i].second]}] = i;
        adj[idx[edges[i].first]].push_back({idy[edges[i].second],i});
        adj[idy[edges[i].second]].push_back({idx[edges[i].first],i});
    }
    int cnt = 0;
    int s = 0;
    f(i,0,sz){
        if((int)adj[i].size() % 2 != 0){
            cnt++;
            s = i;
        }
    }
  //  debug(cnt);
    if(cnt == 1 || cnt > 2) {
        NO;
        return;
    }
    dfs(s);
   // debug(path);
   // debug(sz);
    if(path.size() != n+1) NO;
    else{
        reverse(all(path));
        YES;
        bool flip = true;
        if(path[0] < xx.size()) flip = false;
        for(int i = 0 ; i < (int)path.size() - 1 ; i++){
                if((i&1) ^ flip)
                cout<<mp[{path[i+1],path[i]}]+1<<" ";
                else 
                cout<<mp[{path[i],path[i+1]}]+1<<" ";
        }
        cout<<ln;
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