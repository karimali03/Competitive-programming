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

// Counts occurrences of bit x being 1 in the range [0, n]
int calc(int bit,int r){
    if(r<=0) return 0;
    int blk = (1ll << (bit+1));
    int mid = blk >> 1ll;
    int ret = ( (r+1) / blk) * mid;
    int rem = (r+1) % blk;
    if(rem > mid) ret += (rem - mid);
    return ret; 
}

int get(int bit,int l,int r){
    return calc(bit,r) - calc(bit,l-1);
}

const int MOD = 1e9+7;
void solve(int test_case) {
    int x,y,k; cin>>x>>y>>k;
    int x2 = x + k - 1;
    int y2 = y + k - 1;
    int res = 0;
    for(int i = 0; i < 61 ; i++){
        int x1 = get(i,x,x2);
        int x0 = x2-x+1 - x1;
        int y1 = get(i,y,y2);
        int y0 = y2-y+1 - y1;
        x0 %= MOD; y0 %= MOD;
        x1 %= MOD; y1 %= MOD;
        int cur = x0 * y1 % MOD;
        (cur += (x1 * y0)%MOD)%=MOD;
        (cur *= ((1ll << i)%MOD))%=MOD;
        (res += cur)%=MOD;
    }
    cout<<res<<ln;
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