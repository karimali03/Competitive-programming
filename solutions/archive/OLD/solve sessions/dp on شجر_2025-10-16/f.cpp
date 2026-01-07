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
    vi v(n); cin>>v;
    vii g(n);
    for(int i=1;i<n;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vii dp(n,vi(k+5,-1));
    function<int(int,int,int)> rec = [&](int x,int p,int ch)->int{
        int &ret = dp[x][ch];
        if(~ret) return ret;
        vi sum(k+2);
        for(auto it : g[x])if(it!=p){
            for(int a = max(0ll,ch-1) ; a <= k+1 ; a++) sum[a]+=rec(it,x,a);
        }
        ret = 0;
        if(ch == 0) ret = v[x] + sum[k];
        int nch = max(0ll,ch-1);
        for(auto it : g[x])if(it!=p){
            for(int a = nch ; a <= k+1 ; a++){
                int b = min(k+1,max({nch , k-a-1 }));
                int mn = min(a,b);
                int mx = max(a,b);
                ret = max(ret , rec(it,x,mn) + sum[mx] - rec(it,x,mx) );
            }
        }
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