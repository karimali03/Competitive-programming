#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pl pair<ll, ll>
#define vp vector<pl>
#define vi vector<ll>
#define vii vector<vi>

const ll INF  = 1e16;
const int N = 1e5+10;
const int K = 26;

ll dp[N][K]{};
ll X[N];

ll C(ll i, ll j) {
    if (i >= j) return 0;
    ll len = j - i;
    ll mid = i + 1 + len/2;
    
    ll ret = 0;
    ll pos = X[mid] - X[mid-1];
    // cout << j << "|\n";
    ret += (mid-i)*pos - X[mid]+X[i];
    ret += X[j]- X[mid] - (j-mid)*pos;

    // if (ret < 0) cout << i << ' ' << j << "|\n";
    return ret;
}

void dac(ll k, ll l, ll r, ll optl, ll optr) {
    if (l > r) return;

    ll mid = (l+r)>>1;
    pl best = {INF, optl};

    for (int i = optl; i <= min(mid, optr); i++)
    {
        ll c = C(i, mid);
        best = min(best, pl(dp[i][k-1] + c, i));
    }
    
    dp[mid][k] = best.first;
    ll opt = best.second;
    dac(k, l, mid-1, optl, opt);
    dac(k, mid+1, r, opt, optr);
}

void solve(){
    ll n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> X[i];
    }
    sort(X+1, X+n+1);
    for (int i = 1; i <= n; i++)
    {
        X[i] += X[i-1];
    }
        
    for (int i = 0; i <= n; i++) dp[i][0] = INF;
    dp[0][0] = 0;
    // cout << C(0, n) << "|\n";
    // return;
    ll sol = INF;
    for (int i = 1; i <= k; i++)
    {
        dac(i, 1, n, 0, n-1);
        sol = min(sol, dp[n][i]);
        // cout << dp[n][i] << "|\n";
    }
    
    cout << sol << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
