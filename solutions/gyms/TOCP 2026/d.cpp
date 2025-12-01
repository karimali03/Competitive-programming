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
    string s; cin>>s;
    if((int)s.size() == 1){
        cout<<"0\n";
        return;
    }
    int n = s.size();
    vii dp(n,vi(n,-1));
    function<int(int,int)> rec = [&](int x,int y) -> int{
        if(x+1 == y) return (s[x] != s[y]);
        if(x == y) return 0;
        int &ret = dp[x][y];
        if(~ret) return ret;
        ret = min({rec(x+1,y) , rec(x,y-1) , rec(x+1,y-1)}) + 1;
        if(s[x] == s[y]) ret = min(ret , rec(x+1,y-1));
        return ret;
    };
    cout<<rec(0,n-1)<<ln;
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