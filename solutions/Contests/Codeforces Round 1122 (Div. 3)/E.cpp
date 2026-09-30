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
// spf ( smallest prime factor )
int spf[N];
vector<int> fc[N]{};
// log(n)
void fast_fact(int n){
    int x = n;
    while(n > 1){
        if(fc[x].empty() || fc[x].back() != spf[n])fc[x].push_back(spf[n]);
        n /= spf[n];
    }
}
//  O(n*log(log(n)))
void SPF(){
    for(int i = 2 ; i < N ; i++) spf[i] = i;
    for(int i = 2 ; i*i < N ; i++){
        if(spf[i] == i) 
        // start at i*i because smaller multiples are already marked by smaller primes.
        for(int j = i*i ; j < N ; j += i) if(spf[j] == j) spf[j] = i;
    }
    for(int i = 2 ;i  < N ; i++) fast_fact(i);
}

int n,k;
int dp[N]{};
int vis[N]{};
int cnt = 0;
int rec(int x){
    if(vis[x] == cnt) return dp[x];
    vis[x] = cnt;
    if(x <= k) return dp[x] = 0;
    int cur = 1e9;
    for(auto &it : fc[x]){
        if(x/it <= k) cur = 1;
        else cur = min(cur ,1 + it * rec(x/it));
    }
    return dp[x] = cur;
}
void solve(int test_case) {
    cin>>n>>k;
    cnt++;
    ll res = 0;
    for(int i =0 ;i < n ; i++){
        int x; cin>>x;
      //  cout<<x<<" "<<rec(x)<<ln;
        res += rec(x);
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