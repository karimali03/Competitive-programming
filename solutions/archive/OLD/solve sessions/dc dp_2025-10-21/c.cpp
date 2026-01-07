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
const int N = 5005;
int a[N],c[N];
int n,b;
vii g;
int sz[N]{};
int dp[N][N][2];
void rec(int x){
       dp[x][0][0] = 0;
        dp[x][1][0] = a[x];
        dp[x][1][1] = a[x] - c[x];
        sz[x] = 1;
        for(auto it : g[x]){
            rec(it);
            int m1 = sz[x] , m2 = sz[it];
            vii res(m1+m2);
            for(int i = m1 ; i >= 0; i--){
                for(int j = m2;j >= 0 ; j--){
                    dp[x][i+j][0] = min(dp[x][i+j][0],dp[x][i][0]+dp[it][j][0]);
                    if(i) dp[x][i+j][1] = min(dp[x][i+j][1],dp[x][i][1]+min(dp[it][j][1],dp[it][j][0]));
                }
            }
            sz[x]+=sz[it];
        }
}

void solve(int test_case) {
  cin>>n>>b;
  g = vii(n);
  for(int i = 0 ;i < n ; i++){
        cin>>a[i]>>c[i];
        if(i){
            int x; cin>>x; x--;
            g[x].push_back(i);
        }
   }
   f(i,0,n+1) f(j,0,n+1) f(k,0,2) dp[i][j][k] = 1e16;
    rec(0);
    for(int i = n ; i >= 0 ; i--){
        if(min(dp[0][i][0],dp[0][i][1]) <= b){
            cout<<i<<ln;
            return;
        }
    }
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