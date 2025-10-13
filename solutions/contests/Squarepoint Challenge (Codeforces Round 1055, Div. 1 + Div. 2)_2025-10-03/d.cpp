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
// get the most significant bit
int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}


map<int,int>dp;
int rec(int x){
    if(dp.count(x)) return dp[x];
    int cnt = 0;
    int xx = x;
    while(x > 1){
        if(co(x+1) == 1){
            cnt += rec(x+1);
            break;
        } 
        x/=2; cnt++;
    }
    return dp[xx] = cnt;
}
void solve(int test_case) {

    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    int ans = 0;
    for(int i = 0 ;  i < n; i++){
        cout<<v[i]<<" "<<rec(v[i])<<ln;
        ans += rec(v[i]);
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