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

const int N = 200005;
int dp[N][3][21][2];
int vis[N][3][21][2]{};
int v[N];
int n,k;
int rec(int i,int st,int fl,int ex){
        if(i == n) return st == 2 ? 0 : -1e16;
        int &ret = dp[i][st][fl][ex];
        if(vis[i][st][fl][ex]) return ret;
        if(st == 0) ret = max(rec(i+1,st,fl,ex),rec(i+1,st+1,fl,ex));
        else if(st == 1){
            if(ex){
                ret = v[i] + max(rec(i+1,st,fl+1,0),rec(i+1,st+1,fl+1,0));
                ret = max(ret , -v[i] + max(rec(i+1,st,fl,1),rec(i+1,st+1,fl,1)));
            }else{
                ret = v[i] + max(rec(i+1,st,fl,ex),rec(i+1,st+1,fl,ex));
                if(fl < k) ret = max(ret , -v[i] + max(rec(i+1,st,fl,1),rec(i+1,st+1,fl,1)) );
            }
        } 
        else ret = rec(i+1,st,fl,ex);
        vis[i][st][fl][ex] = 1;
        return ret;
}
// 0 0 0 0 0 1 1 1 1 1 2 2 2 2 2 
void solve(int test_case) {
   cin>>n>>k;
   f(i,0,n) cin>>v[i];
   int ans = max(rec(0,1,0,0),rec(0,0,0,0));
   cout<<ans<<ln;
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