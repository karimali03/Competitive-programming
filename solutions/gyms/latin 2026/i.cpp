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

const int N = 505;
int dp[N][N];
int vis[N][N]{};
int cnt = 0;
void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii g(2*n+1) , rg(2*n+1);
    for(int i = 0;i < m ; i++){
        int x,y; cin>>x>>y;
        g[x].push_back(y);
    }   
    int en;
    function<int(int,int)> rec = [&](int x,int y) -> int{
        if(x == en && y == n) return 1;
        if(x == y) return 0;
        int &ret = dp[x][y];
        if(vis[x][y] == cnt) return ret;
        vis[x][y] = cnt;
        ret = 0;
        if(x < y && x != en){
            for(auto it : g[x]){
                if(it > en) continue;
                ret = ret | rec(it,y);
            }
            return ret;
        }
        for(auto it : g[y+n]){
            ret = ret | rec(x,it-n);
        }
        return ret;
    };
    vi l , r;
    function<void(int,int)> build = [&] (int x,int y){
        if(x == en && y == n) return;
        if(x < y){
            for(auto it : g[x]){
                if(it > en) continue;
                if(rec(it,y)){
                    l.push_back(it);
                    build(it,y);
                    return;
                }
            }
        }
        for(auto it : g[y+n]){
            if(rec(x,it-n)){
                r.push_back(it);
                build(x,it-n);
                return;
            }
        }
    };
    for(int mid = 1 ; mid < n ; mid++){
        cnt++;
        en = mid;
        for(auto it : g[mid]){
            if(it <= n+1) continue;
            if(rec(1,it-n)){
                l.push_back(1);
                r.push_back(it);
                build(1,it-n);
                int sz = l.size() + r.size();
                cout<<sz<<ln;
                for(auto &a : l) cout<<a<<" ";
                for(auto &b : r) cout<<b<<" ";
                cout<<ln;
                return;
            }
        }
    }
    cout<<"*\n";
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