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
    map<int,int>frq;
    for(int  i =0 ;i < n ; i++){
        frq[v[i]]++;
    }
    // reach false -> true
    // frq even -> true
    vector<pair<int,int>>g;
    for(auto &[a,b] : frq){
        g.push_back({a,b});
    }
    int sz = g.size();
    vector<bool> dp(sz+1);
    int mn_val = 1e9;
    bool can = false;
    for(int i = sz-1;i >= 0 ; i--){
        auto [a,b] = g[i];
        if(mn_val <= a+k){
            dp[i] = true;
        }
        else{
            dp[i] = (b%2 == 0);
        }
        if(!dp[i]){
            mn_val = a;
        }
        if(dp[i]) can = true;
    }
    if(can) YES;
    else NO;
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