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
const int N = 105;
int dp[N][N][2];
int v[N];
int n,odd;
int rec(int i,int od_cnt,int sum){
    if(i == n || od_cnt == 0) return sum;
    int &ret = dp[i][od_cnt][sum];
    if(~ret) return ret;
    int ev_cnt = n - odd - i + (odd - od_cnt);
    //cout<<i<<" "<<od_cnt<<" "<<ev_cnt<<" "<<sum<<ln;
    int ch1 =  rec(i+1,od_cnt-1, (i&1) ? sum : sum^1);
    int ch2 = ev_cnt ? rec(i+1,od_cnt,sum) : -1;
    if(i&1){
        if(ch1 == 1 || ch2 == 1) return ret = 1;
        return ret = 0;
    }
    if(ch1 == 0 || ch2 == 0) return ret = 0;
    return ret = 1;
}

void solve(int test_case) {
    cin>>n;
    odd = 0;
    for(int i =0  ;i < n ; i++){
        cin>>v[i];
        if(v[i]&1) odd++;
    } 
    memset(dp,-1,sizeof(dp));
    if(rec(0,odd,0)) cout<<"Bob\n";
    else cout<<"Alice\n";
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
