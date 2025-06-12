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
vi vis;
map<pair<int,int>,int>mp;
int cx,cy;

bool dfs(int x){
    if(vis[x]) cx++;
    else cy++;
  //  debug(vis[x]); debug(x);
    for(auto it : adj[x]){
        int expect = mp[minmax(it,x)];
      //  debug(expect);
        if(vis[x] == 0) expect = 1 - expect;
      //  debug(expect);
        if(vis[it] == -1){
            vis[it] = expect; 
            if(!dfs(it)) return false;
        }else if(vis[it] != expect) return false;
    }
    return true;
}
void solve(int test_case) {
    int n,m; cin>>n>>m;   
    mp.clear();
    vis = vi(n,-1); adj = vii(n);
    bool valid = true;
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        string s; cin>>s;
        int val = (s == "imposter" ? 0 : 1);
     //   debug(x); debug(y);
    //    debug(s); debug(val); 
        if(mp.count(minmax(x,y))) {
            if(mp[minmax(x,y)] != val) valid = false;
        }
        else {
            mp[minmax(x,y)] = val;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }
  //  cout<<mp[minmax(0,2)]<<ln;
    if(!valid) return void(cout<<-1<<ln);
    int cnt = 0;

    for(int i = 0 ; i < n ; i++){
        if(vis[i] == -1){
            vis[i] = 1;
            cx = 0 , cy = 0;
            auto res = dfs(i);
            if(!res) return void(cout<<-1<<ln);
            cnt+=max(cx,cy);
        }
    }
    cout<<cnt<<ln;
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