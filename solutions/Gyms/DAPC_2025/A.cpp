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

int n,l,h; 
const int N = 1005;
int dp[N];   
int cnt[21][N];
int rec(int x){
    if(x == n) return 1e9;
    int &ret = dp[x];
    if(~ret) return ret;
    ret = 1;
    int d = 0;
    for(int y = x+1 ; y < n ; y++){
        int sum = cnt[d][y] - (x ? cnt[d][x-1] : 0);
        while(d <= 20 && sum < (y-x+1)){
            d++;
            sum = cnt[d][y] - (x ? cnt[d][x-1] : 0);
        }
        if(d > 20) break;
        ret = max(ret , min(y-x+1 , rec(y+1)));
    }
    return ret;
}
void solve(int test_case) {
    cin>>n>>l>>h;
    memset(dp,-1,sizeof(dp));

    for(int i = 0;i <  n; i++){
        int a; cin>>a;
        for(int d = -10 ; d <= 10;  d++){
            int cur = d*12 + a;
            if(cur >= l && cur <= h) cnt[d+10][i] = 1;
        }
    }
    for(int j = 0 ; j <= 20 ; j++){
        for(int i = 1;i < n ; i++){
            cnt[j][i] += cnt[j][i-1];
        }
    }
    cout<<rec(0)<<ln;
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