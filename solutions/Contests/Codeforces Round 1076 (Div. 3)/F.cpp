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
    int n,ax,ay,bx,by; 
    cin>>n>>ax>>ay>>bx>>by; 
    int base = bx - ax;
    ax--; bx++;
    vi val = {ax,bx};
    vi x(n),y(n); 
    f(i,0,n){
        cin>>x[i]; val.push_back(x[i]);
    }
    cin>>y;
    sort(all(val));
    val.erase(unique(all(val)),val.end());
    int sz = val.size();
    x.push_back(ax); y.push_back(ay);
    x.push_back(bx); y.push_back(by);
    for(int i = 0;i<n+2;i++) x[i] = lower_bound(all(val),x[i])-val.begin();
    vii dp(sz,vi(2,-1));
    vii lvl(sz);
    f(i,0,n+2){
        lvl[x[i]].push_back(y[i]);
    }
    f(i,0,sz) sort(all(lvl[i]));
  
    function<int(int,int)>rec = [&](int i,int ch) -> int{
        if(i == sz) return 0;
        int &ret = dp[i][ch];
        if(~ret) return ret;
        int l = lvl[i][0] , r = lvl[i].back();
        auto it = lvl[i-1][0];
        if(ch == 1) it = lvl[i-1].back();
        int ch1 = abs(it-r) + abs(r-l) + rec(i+1,0);
        int ch2 = abs(it-l) + abs(l-r) + rec(i+1,1);
        ret = min(ch1,ch2);
        return ret;
    };

    cout<<rec(1,0) + base <<ln;
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