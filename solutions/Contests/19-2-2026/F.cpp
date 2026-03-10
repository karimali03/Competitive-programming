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

bool inter(int x,int y,int z){
    if(x == 0 && y == 0) return z == 0;
    if(x == 0) return true;
    int under_sq = y*y - (4 * x * z);
    if(under_sq < 0) return false;
    return true;
}

void solve(int test_case) {
    int n; cin>>n;
    vector<array<int,3>>v(n);
    f(i,0,n){
        cin>>v[i][0]>>v[i][1]>>v[i][2];
    }
    vi idx(n);
    f(i,0,n) idx[i] = i;
    sort(all(idx),[&](int x,int y){
            return v[x][2] < v[y][2];
    });
    sort(all(v),[](array<int,3>&x,array<int,3>& y){
        return x[2] < y[2];
    });
    vii g(n),g2(n);
    vi vis(n);
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        auto [a,b,c] = v[x];
        for(int j = x+1 ; j < n ; j++){
            if(vis[j]) continue;
            auto [l,r,z] = v[j];
            if(!inter(a-l,b-r,c-z)){
                g[x].push_back(j);
                g2[j].push_back(x);
            }
        }
    };

    for(int i =0 ;i < n ; i++) if(!vis[i]) dfs(i);
   
    vi dp1(n,1),dp2(n,1);
    for(int it = 0;it < n ; it++){
        for(auto &x : g[it]){
            dp1[x] = max(dp1[x] , 1 + dp1[it]);
        }
    }
    for(int it = n-1; it >= 0 ; it--){
        for(auto &x : g2[it]){
            dp2[x] = max(dp2[x] , 1 + dp2[it]);
        }
    }
    vi ans(n);
    for(int i = 0 ;i  < n; i++){
        int res = 0;
        for(auto it : g[i]){
            res = max(res , dp2[it]);
        }
        ans[idx[i]] = dp1[i]+res;
    
    }
    cout<<ans<<ln;
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