#include "bits/stdc++.h"

#define ll long long
#define pl pair<ll, ll>
#define vp vector<pl>
#define vi vector<ll>
#define vii vector<vi>
#define all(X) X.begin(), X.end()
#define int ll
#define f(i,a,n) for(int i = a ; i < n ; i++)
const ll INF = 1e16;

using namespace std;
const int N = 305;
int dp[N][N][N];
int v[N][N];
int suf[N];
int n;
int rec(int idx,int st,int len){
    if(st == len){
        int take = idx - st;
        return suf[len+take];
    }
    int &ret = dp[idx][st][len];
    if(ret == -1e15) return ret;
    ret = rec(idx+1,st+1,len) + v[st][idx];
    int take = idx - st;
    if(len+take < n)
    ret = max(ret , rec(idx+1,st,len) + v[len+take][idx] );
    return ret;
}
void solve() {
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
        }
    }

    f(i,0,n+1) f(j,0,n+1) f(k,0,n+1) dp[i][j][k] = -1e15;
    suf[n] = 0;
    for(int i = n-1 ; i >= 0 ; i--){
        suf[i] = v[i][i] + suf[i+1];
    }

 
    int res = -1e18;
    for(int i = 0 ; i  <= n ; i++) res = max(res , rec(0,0,i));
    cout<<res<<"\n";
 
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);

    ll t =1 ;
    cin >> t;
    while (t--)
    {
        solve();
    }
}