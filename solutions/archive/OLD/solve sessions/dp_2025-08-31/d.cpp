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
#define int ll
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

const int N = 1000005;
ll dp[N][3][2][2];
int n;
vi v;
ll rec(int i,int st,int sw1,int sw2){
        if(i == n) return (sw1^sw2) ? -1e15 : 0;
        ll &ret = dp[i][st][sw1][sw2];
        if(~ret) return ret;
        if(st == 0){
            ret = max(rec(i+1,st,sw1,sw2),rec(i+1,st+1,sw1,sw2));
            if(!sw1) ret = max<ll>(ret , (ll)v[i] + max(rec(i+1,st,1,sw2),rec(i+1,st+1,1,sw2)));
        } 
        else if(st == 1){
            ret = v[i] + max(rec(i+1,st,sw1,sw2),rec(i+1,st+1,sw1,sw2));
            if(!sw2) ret = max<ll>(ret , max(rec(i+1,st,sw1,1) , rec(i+1,st+1,sw1,1)) );
        } 
        else{
            ret = rec(i+1,st,sw1,sw2);
            if(!sw1) ret = max<ll>(ret , (ll)v[i] + rec(i+1,st,1,sw2));
        }
        return ret;
}
// 0 0 0 0 0 1 1 1 1 1 2 2 2 2 2 
void solve(int test_case) {
    cin>>n;
    v = vi(n);   cin>>v;
    reverse(all(v));
    memset(dp,-1,sizeof(dp));
    vi res(n);
    for(int i = 0; i < n ; i++){
        res[i] = max(rec(i,0,0,0),rec(i,1,0,0));
    }
    for(int i = n-1 ; i >= 0 ; i--) cout<<res[i]<<" ";
    cout<<ln;
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