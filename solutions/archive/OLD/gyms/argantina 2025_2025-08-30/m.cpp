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

const int MOD = 998244353;
void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    vii adj(n);
    for(int i = 0; i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    auto bfs = [&](int src) -> int{
        queue<int>q; q.push(src);
        vi dist(n,-1);
        dist[src] = 0;
        while (!q.empty()){
            auto cur = q.front(); q.pop();
            if(cur == 1) return dist[cur];
            for(auto it : adj[cur]){
                if(dist[it] != -1) continue;
                dist[it] = 1 + dist[cur];
                q.push(it);
            }
        }
        return 0;
    };

    int d = bfs(0);
    int days = (d + k - 1) / k;
    viii dp(days,vii(k+1,vi(n,-1)));
    function<int(int,int,int)> rec = [&](int day,int rem,int node) -> int{
        if(day == days) return (node == 1);
        int &ret = dp[day][rem][node];
        if(~ret) return ret;
        ret = rec(day+1,k,node);
        if(!rem) return ret;
        for(auto it : adj[node]){
            (ret += rec(day,rem-1,it))%=MOD;
        }
        return ret;
    };
    cout<<rec(0,k,0)<<ln;
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
