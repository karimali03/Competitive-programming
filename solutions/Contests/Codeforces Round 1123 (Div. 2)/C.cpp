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

const int N = 3e5 + 5;


// spf ( smallest prime factor )
int spf[N];
void SPF(){
    for(int i = 2 ; i < N ; i++) spf[i] = i;
    for(int i = 2 ; i*i < N ; i++){
        if(spf[i] == i) 
        // start at i*i because smaller multiples are already marked by smaller primes.
        for(int j = i*i ; j < N ; j += i) if(spf[j] == j) spf[j] = i;
    }
}
// log(n)
vi fast_fact(int n){
    vi ret;
    while(n > 1){
        if(ret.empty() || ret.back() != spf[n]) ret.push_back(spf[n]);
        n /= spf[n];
    }
    return ret;
}
void solve(int test_case) {
    int n,x; cin>>n>>x;
    vi v(n); cin>>v;
    if(x == 1){
        cout<<0<<ln; return;
    }
    auto X = fast_fact(x);
    int mx = 0;
    for(auto &it : X){
        int res = 0;
        for(auto &a : v){
            if(a%it  == 0) res += a;
        }
        mx = max(mx , res);
    }
    cout<<mx<<ln;
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