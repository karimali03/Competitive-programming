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
    vi d(n); cin>>d;
    vector<vector<pair<int,int>>> g(n);
    for(int i=1;i<n;i++){
        int x,y,w; cin>>x>>y>>w; x--,y--;
        g[x].push_back({y,w}); g[y].push_back({x,w});
    }
   
    const int INF = 1e18;
    vii dp(n,vi(2,INF));
    function<int(int,int,int)> rec = [&](int x,int p,int ch)->int{
        int &ret = dp[x][ch];
        if(ret != INF) return ret;
        if(ch > d[x]) return ret = -INF;
        vi l,r;
       for(auto [a,b] : g[x]) if(a!=p){
            l.push_back(rec(a,x,0));
            r.push_back(b + rec(a,x,1));
        }
        if(!l.empty()){
            int sum = 0;
            vi dif;
            for(int i = 0;i < (int)l.size();i++){
                sum += l[i];
                dif.push_back(r[i]-l[i]);
            }
            sort(rall(dif));
            int ptr = 0;
            ret = sum;
            for(int i = ch ; i < d[x] ; i++){
                ret = max(ret , sum);
                if(ptr < (int)dif.size()) sum += dif[ptr++];
            }
            ret = max(ret , sum);
        }else ret = 0;
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