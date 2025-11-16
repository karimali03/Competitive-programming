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
    vector<pair<int,int>> pre(n);
    vector<pair<int,int>> suf(n);
    vii v(2,vi(n));
    cin>>v[0]>>v[1];
    pre[0] = {v[0][0],v[0][0]};
    suf[n-1] = {v[1][n-1],v[1][n-1]};
    for(int i = 1; i < n; i++) 
    pre[i] = {min(v[0][i],pre[i-1].first) , max(v[0][i],pre[i-1].second)};
    for(int i = n-2 ; i >= 0 ; i--)
    suf[i] = {min(v[1][i],suf[i+1].first) , max(v[1][i],suf[i+1].second)};
    vi res(2*n+2,1e10);
    for(int i = 0;i < n ; i++){
        int l = min(pre[i].first,suf[i].first);
        int r = max(pre[i].second,suf[i].second);
        res[l] = min(res[l] , r);
    }
    int ans = 0;
    for(int i = 2*n ; i >= 1 ; i--){
     //   cout<<i<<" "<<res[i]<<ln;
        res[i] = min(res[i] , res[i+1]);
        if(res[i] == 1e10) continue;
        ans += (2*n-res[i]+1);
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