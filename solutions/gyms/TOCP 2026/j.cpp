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
    int n,k; cin>>n>>k;
    int l = 1 , r = 1e16;
    vector<vector<pair<int,int>>> g(n);
    for(int i = 1  ; i < n ; i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
        l = max( l , w);
    }
    vi dis(n);
    int kk = 0;
    int mx = 0;
    function<void(int,int)> dfs = [&](int x,int p){
        int mx1 = -1 , mx2 = -1;
        int cur = 0;
        for(auto [y,w] : g[x]) if(y != p){
            dfs(y,x);
            dis[y] += w;
            if( dis[y] > mx) kk++ , dis[y] = w;
            if(mx1 == -1 || dis[y] > dis[mx1]) mx2 = mx1 , mx1 = y;
            else if(mx2 == -1 || dis[y] > dis[mx2]) mx2 = y;

            cur = max(cur , dis[y]);
        }
        if(mx1 != -1 && mx2 != -1 && dis[mx1] + dis[mx2] > mx){
            kk++;
            cur = 0;
        }
        dis[x] = cur;
    };
  
    int ans = r;
    while(l<=r){
        int mid = l + (r-l)/2;
        mx = mid; kk = 0;  dfs(0,-1);
        if(kk <= k){
            ans = mid;
            r = mid-1;
        }else l = mid+1;
    }
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