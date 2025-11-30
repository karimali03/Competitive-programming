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


const int MOD = 1e6+3;
int fact[MOD],invfact[MOD];

void solve(int test_case) {
    int n; cin>>n;
    vi a(n),b(n); cin>>a>>b;

    int res = 1;
    int cnt = 0;
    int finish = false;
    while(!finish){
        for(int i = 0; i < n ; i++){
            if(b[i] == a[i]) finish = true;
            else if(b[i]/2 < a[i]) finish = true;
        }
        if(finish){
            int sum = 0;
            for(int i = 0 ; i < n ; i++) sum += b[i]-a[i];
            cnt += sum;
            if(sum >= MOD) res = 0;
            else{
                (res *= fact[sum])%=MOD;
                for(int i = 0 ; i < n;  i++){
                    res *= invfact[b[i]-a[i]];
                    res %=MOD;
                }
            }
            break;  
        }
        int od = 0;
        for(int i = 0;i < n ; i++) if(b[i]&1) b[i]--,od++;
        if(od){
            (res *= fact[od])%=MOD;
            cnt+=od;
        }else{
            f(i,0,n) b[i]/=2;
            cnt++;
        }
    }
    cout<<cnt<<" "<<res<<ln;
    
}
int fp(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    fact[0] = 1;
    invfact[0] = fp(fact[0],MOD-2);
    for(int i = 1 ; i < MOD ; i++){
        (fact[i] = i * fact[i-1])%=MOD;
        invfact[i] = fp(fact[i],MOD-2);
    }
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}