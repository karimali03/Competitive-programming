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
    int n; cin>>n;
    vi v(n); cin>>v;
    vii g(n);
    for(int i = 1 ; i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vii dp(n,vi(2,-1));
    function<int(int,int,int)> rec = [&](int x,int p,int up) -> int {
        int &ret = dp[x][up];
        if(~ret) return ret;
        vi low,high;
        for(auto it : g[x]) if(it != p){
            low.push_back(rec(it,x,0));
            high.push_back(rec(it,x,1));
        }
        int sz = low.size();
        if(sz){
            vi ac(sz);
            for(int i = 0 ;i < sz ; i++) ac[i] = low[i] - high[i];
            sort(rall(ac));
            int cur = 0;
            for(int i = 0 ;i < sz;  i++) cur += high[i];
            int pt = 0;
            for(int deg = up ; deg <= sz+up ; deg++){
                ret = max(ret , v[deg] + cur);
                cur += ac[pt++];
            }
        }
        else ret = v[up];
        return ret;
    };
    cout<<rec(0,-1,0)<<ln;
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