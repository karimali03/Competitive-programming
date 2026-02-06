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


// get the most significant bit
int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}

const int MOD = 998244353;

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b>>=1;
    }
    return res;
}

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int z = 0;
    vi cnt(31);
    vector<set<int>>st(31);
    map<int,int>mp;
    for(int i = 0;i < n ; i++){
        if(v[i] == 0) z++;
        else{
            mp[v[i]]++;
            st[MSB(v[i])].insert(v[i]);
            cnt[MSB(v[i])]++;
        } 
    }
    int cur = ( z*z % MOD + 3 * z * (n - z) % MOD ) % MOD;
    int sum = n - z;
    cout<<cur<<ln;
    for(int i = 30 ; i >= 0 ; i--){
        sum -= cnt[i];
        (cur += 3 * cnt[i] * sum)%=MOD;
        for(auto &it : st[i]){
            int rem = cnt[i] - mp[it];
            int c = mp[it];
            (cur += 2 * rem * c)%=MOD;
            (cur += 3 * c * c)%=MOD;
        }
    }
   
    int ans = (cur * fp(n*n,MOD-2))%MOD;
    cout<<ans<<ln;
  
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