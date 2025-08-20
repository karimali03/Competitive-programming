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

const int N = 300005;
vector<int> g[N];
pair<int,int> v[N];
void solve(int test_case) {
    int n,m; cin>>n>>m;
    for(int i = 0 ;i < n ; i++) cin>>v[i].first>>v[i].second;
    for(int i = 0 ; i < m ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi lvl(n,-1);
    queue<int>q;
    q.push(0);
    lvl[0] = 0;
    while(!q.empty()){
        auto x = q.front(); q.pop();
        for(auto it : g[x]){
            if(lvl[it] == -1){
                lvl[it] = 1 + lvl[x];
                q.push(it);
            }
        }
    }
    vector<pair<int,int>>mx(n);
    vector<int>res(n);
    int k = *max_element(all(lvl));
    vii nodes(k+1);
    for(int i = 0 ;i <  n ;i++) nodes[lvl[i]].push_back(i);
    
    for(int i = 0 ;i  < n ; i++){
        // k+1
        mx[i] = {v[i].first - v[i].second * (lvl[i]+1) ,i};
    }
    sort(all(mx));
    for(int i = 0 ; i < n ;i++){
        res[i] = mx.back().first;
        if(i == mx.back().second) res[i] = mx[n-2].first;
        res[i] = max(res[i] , v[0].first - v[0].second);
    }
   

    // k-1
    vi dp(n,-1);
    function<int(int)> dfs = [&](int x) -> int{
        int &ret = dp[x];
        if(~ret) return ret;
        ret = v[x].first - v[x].second * (lvl[x]-1);
        for(auto it : g[x]){
            if(lvl[it] > lvl[x]) ret = max(ret , dfs(it));
        }
        return ret;
    };
    vii dp2(n,vi(2,-1));
    function<int(int,int)> dfs2 = [&](int x,int st) -> int{
        int &ret = dp2[x][st];
        if(~ret) return ret;
        ret = v[x].first - v[x].second * lvl[x];
        for(auto it : g[x]){
            if(!st && lvl[it] == lvl[x]) ret = max(ret, dfs2(it,1));
            else if(lvl[it] > lvl[x]) ret = max(ret , dfs2(it,st));
        }
        return ret;
    };

    for(auto a : nodes[1]){
    //    cout<<a<<" ";
        for(auto it : g[a]){
            if(lvl[it] > lvl[a]) res[a] = max({res[a] , dfs(it) , dfs2(it,0)});
            else if(lvl[it] == lvl[a]) res[a] = max(res[a] , dfs2(it,1));
        }
    }

    for(auto a : nodes[1]) cout<<res[a]<<"\n";

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