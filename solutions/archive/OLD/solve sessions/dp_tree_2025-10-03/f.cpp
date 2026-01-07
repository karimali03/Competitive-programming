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
    int n,c; cin>>n>>c;
    vi v(n); cin>>v;
    vii g(n);
    for(int i = 1 ; i< n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    const int INF = 1e16;
    viii dp(n,vii(2,vi(2,INF)));
    function<int(int,int,int,int)> rec = [&](int x,int p,int ch,int prv) -> int{
        int &ret = dp[x][ch][prv];
        if(ret != INF) return ret;
        ret = ch ? v[x] : 0;
        if(ch && prv) ret -=2*c;
        for(auto it : g[x]) if(it != p){
            ret += max({0ll , rec(it,x,1,ch), rec(it,x,0,ch)});
        }
        return ret;
    };
    cout<<max(rec(0,-1,0,0),rec(0,-1,1,0))<<ln;
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