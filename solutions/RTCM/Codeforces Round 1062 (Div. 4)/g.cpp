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


const int N = 8005;
int v[N],c[N];
int n;
// ll rec(int i,int j){
//     if(i == n+1) return 0;
//     ll &ret = dp[i][j];
//     if(~ret) return ret;
//     ret = rec(i+1,j);
//     if(v[i] >= v[j]) ret = max(ret ,(ll) c[i] + rec(i+1,i));
//     return ret;
// }
void solve(int test_case) {
    cin>>n;
    v[0] = -1;
    ll sum = 0;
    f(i,1,n+1) cin>>v[i];
    f(i,1,n+1) cin>>c[i],sum+=c[i];
    vector<ll> dp(n+1,0);
    for(int i = n ; i >= 1 ; i--){
        vector<ll> cur(n+1);
        for(int j = n-1 ; j >= 0 ; j--){
            cur[j] = dp[j];
            if(v[i] >= v[j]) cur[j] = max<ll>(cur[j] , c[i] + dp[i]);
        }
        dp = cur;
    }
    cout<<sum-dp[0]<<ln;
}

int main() {
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