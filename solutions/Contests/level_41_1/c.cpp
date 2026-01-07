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
    vii v(n);
    vi val;
    for(int i = 0;i < n;  i++){
        int x; cin>>x;
        for(int j = 0;j < x ; j++){
            int c; cin>>c;
            if(v[i].empty() || c > v[i].back()) v[i].push_back(c),val.push_back(c);
        }
    }
    sort(all(val));
    val.erase(unique(all(val)),val.end());
    int mx = val.size();
    vi dp(mx+5);
    vii frq(mx+5);
    for(int i = 0;i < n ; i++){
        for(auto &it : v[i]) it = lower_bound(all(val),it)-val.begin()+1;
        frq[v[i].back()].push_back(i);
    }

    for(int i = 1;i <= mx ; i++){
        dp[i] = max(dp[i] , dp[i-1]);
        for(auto &it : frq[i]){
            int sz = v[it].size();
            for(int j = 0;j < sz ; j++){
                dp[i] = max(dp[i] , sz-j + dp[v[it][j]-1]);
            }
        }
    }

    cout<<dp[mx]<<ln;
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