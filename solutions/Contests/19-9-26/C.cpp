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
const int N = 1e6+5;
// spf ( smallest prime factor )
int spf[N];
//  O(n*log(log(n)))
void SPF(){
    for(int i = 2 ; i < N ; i++) spf[i] = i;
    for(int i = 2 ; i*i < N ; i++){
        if(spf[i] == i) 
        // start at i*i because smaller multiples are already marked by smaller primes.
        for(int j = i*i ; j < N ; j += i) if(spf[j] == j) spf[j] = i;
    }
}
// log(n)
map<int,int> fast_fact(int n){
    map<int,int>ret;
    while(n > 1){
        ret[spf[n]]++;
        n /= spf[n];
    }
    return ret;
}

int fp(int x,int y){
    int ret = 1;
    while(y > 0){
        if(y&1) ret = ret * x;
        x = x*x; y >>=1;
    }
    return ret;
}
void solve(int test_case) {
    int n; cin>>n;
    auto fac = fast_fact(n);
    int res = (int)fac.size() - 1;
    for(auto &[a,b] : fac){
        res += b;
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SPF();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}