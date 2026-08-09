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



void solve(int test_case) {
    int n,m; cin>>n>>m;
    viii md(11,vii(11));
    for(int x = 1 ; x <= 10 ; x++){
        for(int i = 1; i <= n ; i++) md[x][i%x].push_back(i);
    }
    vector<vector<vector<pair<int,int>>>> rng(11,vector<vector<pair<int,int>>>(11));
    for(int i = 0;i < m ; i++){
        int a,d,k; cin>>a>>d>>k;
        int rem = a%d;
        auto cur = lower_bound(all(md[d][rem]),a) - md[d][rem].begin();
        rng[d][rem].push_back({cur,cur+k});
    }
    vii g(n);
    for(int d = 1; d <= 10 ; d++){
        for(int x = 0; x < d; x++){
            if(rng[d][x].empty()) continue;
            sort(all(rng[d][x]));
            vector<pair<int,int>> nr = {rng[d][x][0]};
            for(auto &[l,r] : rng[d][x]){
                if(nr.back().second >= l){
                    nr.back().second = max(r , nr.back().second);
                }else nr.push_back({l,r});
            }
            for(auto &[l,r] : nr){
                int X = md[d][x][l];
                for(int a = l+1 ; a <= r ; a++){
                    int Y = md[d][x][a];
                    g[X-1].push_back(Y-1);
                    g[Y-1].push_back(X-1);
                }
            }
        }
    }


    vi vis(n);
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto &it : g[x]) if(!vis[it]) dfs(it);
    };
    int cc = 0;
    for(int i = 0;i < n ; i++){
        if(!vis[i]){
            cc++; dfs(i);
        }
    }
    cout<<cc<<ln;
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