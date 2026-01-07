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
    vi sum(n),res(n),ac(n);
    cin>>sum;
    vii adj(n);
    f(i,0,n-1){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }   
    res[0] = sum[0];
    ac[0] = sum[0];
    queue<pair<int,int>>q;
    for(auto it : adj[0]) q.push({it,0});
    int lvl = 1;
    vi mn(n),mx(n);
    mn[0] = mx[0] = sum[0];
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto [x,p] = q.front(); q.pop();
            if(lvl&1) ac[x] = -sum[x] + ac[p];
            else ac[x] = sum[x] + ac[p];
            mn[x] = min(ac[x] , mn[p]);
            mx[x] = max(ac[x],mx[p]);
            res[x] = sum[x];
        //    cout<<x<<" "<<mx[x]<<" "<<mx[x]<<" "<<ac[x]
            if(lvl&1) res[x] = max({ -ac[x] , res[x] , -ac[x] + mn[p], -ac[x] +mx[p] });
            else res[x] = max({ ac[x] , res[x] , ac[x]-mn[p] , ac[x]-mx[p]});
            for(auto it : adj[x]) if(it!=p) q.push({it,x});
        }
        lvl++;
    }
    for(auto it : res) cout<<it<<" ";
    cout<<ln;
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