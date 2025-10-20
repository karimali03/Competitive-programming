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

const int MOD = 1e9+7;

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b>>=1;
    }

    return res;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n-1); cin>>v;
    vii g(n);
    for(int i = 1 ; i <= n-1 ; i++){
        g[i].push_back(v[i-1]);
        g[v[i-1]].push_back(i);
    }
    vi c(n); cin>>c;
    vii dp(n,vi(2,-1));
    function<int(int,int,int)> rec = [&](int x,int p,int ch) -> int{
        int &ret = dp[x][ch];
        if(~ret) return ret;
        if(ch == 0 && c[x] == 1) return 0;
        int black = 1;
        int all = 1;
        for(auto it : g[x]) if(it != p){
            int a = rec(it,x,0);
            int b = rec(it,x,1);
            (black*=a)%=MOD;
            (all*=(a+b))%=MOD;
        }
     //   cout<<x<<" "<<ch<<" "<<black<<" "<<all<<ln;
        if(ch == 0 || (ch == 1 && c[x] == 1)) ret = all;
        else{
            ret = 0;
            for(auto it : g[x]) if(it != p){
                int b = rec(it,x,1); int a = rec(it,x,0);
                int sum = (all * fp((a+b),MOD-2))%MOD;
                (sum*=b)%=MOD;
                (ret+=sum)%=MOD;
            }
        }
        return ret;
    };
    cout<<rec(0,-1,1)<<ln;
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