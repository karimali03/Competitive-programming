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

const int N = 200005;
const int SQ = 320;
vector<pair<int,int>>adj[N];
void solve(int test_case) {
    int n,q; cin>>n>>q;
    f(i,0,n) adj[i].clear();
    vi v(n); cin>>v;
    vi cnt(n);
    vi edg(n);
    int res = 0;
    for(int i = 0 ; i < n ; i++){
        int x,y,z; cin>>x>>y>>z; x--,y--;
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
        edg[i] = z;
        if(v[x] != v[y]) res+=z;
        cnt[x]++,cnt[y]++;
    }
    vi l;
    map<pair<int,int>,int>xx;
    for(int i = 0 ; i < n ; i++){
        if(cnt[i] < SQ){
            l.push_back(i);
             for(auto [a,b] : adj[i]){
                    xx[{i,a}] = b;
             }
        } 
    }
    while(q--){
        int u,x; cin>>u>>x; u--;
        if(cnt[u] <= SQ){
            for(auto [a,b] : adj[u]){
                if(v[u] != v[a]) res-=b;
            }
            v[u] = x;
            for(auto [a,b] : adj[u]){
                if(v[u] != v[a]) res+=b;
            }
        }
        else{
            vector<pair<int,int>>cur;
            for(auto it : l){
                if(xx.count({it,u})){
                    if(v[it] != v[u]) res-=xx[{it,u}];
                    cur.push_back({it,xx[{it,u}]});
                }
            }
            v[u] = x;
            for(auto &it : cur){
                if(v[u] != v[it.first]) res+=it.second;
            }

        }
        cout<<res<<ln;
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