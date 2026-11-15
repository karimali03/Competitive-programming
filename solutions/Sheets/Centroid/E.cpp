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
 
 
const int N = 200005;
vector<int> g[N];
int sz[N];
bool del[N];

int n,k1,k2;
ll ans = 0;

int get_size(int u,int p){
    sz[u] = 1;
    for(auto &it : g[u]) if(it != p && !del[it]){
        sz[u] += get_size(it,u);
    }
    return sz[u];
}
int get_centroid(int u,int p,int tot){
    for(auto &it : g[u]) if(it != p && !del[it]){
        if(sz[it] * 2 > tot) return get_centroid(it,u,tot);
    }
    return u;
}
 
void add(int u,int p,int d,vector<int>&cur){
    if(d > k2) return;
    cur.push_back(d);
    for(auto &it : g[u]) if(it != p && !del[it]){
        add(it,u,d+1,cur);
    }
}

ll calc(vector<int>&v){
    int mx = *max_element(all(v));
    vi frq(mx+1);
    for(auto &it : v) frq[it]++;
    vector<ll> pre(mx+1);
    for(int i=0;i<=mx;i++){
        pre[i] = frq[i];
        if(i) pre[i] += pre[i-1];
    }
    ll ret = 0;
    for(int i = 0;i <= mx; i++){
        int l = max(0,k1-i); int r = min(mx,k2-i);
        if(l <= r){
            ret += frq[i] * (pre[r] - (l ? pre[l-1] : 0));
            if(i >= l && i <= r) ret -= frq[i];
        }
    }
    return ret/2;
}
void decompose(int x){
    int size = get_size(x,-1);
    int cent = get_centroid(x,-1,size);
    // calc answer for this centroid
    vector<int>d = {0};
    for(auto &it : g[cent]) if(!del[it]){
        vector<int>cur;
        add(it,cent,1,cur);
        ans -= calc(cur);
        for(auto &it : cur) d.push_back(it);
    }
    ans += calc(d);
    // clear datastructure for next centroid
    del[cent] = true;
    // decompose for next centroid
    for(auto &it : g[cent]) if(!del[it]){
        decompose(it);
    }
}
 
void solve(int test_case) {
    cin>>n>>k1>>k2;;
    for(int i = 1 ; i < n; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    decompose(0);
    cout<<ans<<ln;
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