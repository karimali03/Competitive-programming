#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
 
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

int fp(int a, int b, int m) {
    int res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

const int N = 3'000'01;
const int MOD = 998244353;
int fact[N],inv_fact[N];
void pre_compute(){
    fact[0]  = inv_fact[0] = 1;
    for(int i = 1 ; i < N ; i++) 
    fact[i] = ( i%MOD * fact[i-1]%MOD )% MOD;
    for (int i = 1; i < N; i++) 
    inv_fact[i] = fp(fact[i],MOD-2,MOD);

}

int ncr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}


void solve(int test_case){
     pre_compute(); 
 
    int n; cin>>n;
    vi v(n); cin>>v;
    int cnt[300001]{};

    for(int i = 0 ; i < n ; i++) cnt[v[i]]++;
    int dp[300001]{}; // number of ways to choose elements with gcd equal k
    for(int i = 1 ; i <= 20 ; i++){
        for(int a = 300000 ; a >= 1 ; a--){
            int c = cnt[a];
            dp[a] = 0;
            for(int x = 2*a ; x <= 300000 ; x+=a) c+=cnt[x],dp[a]-=dp[x];
            (dp[a] += ncr(c,i))%=MOD;
        }
        if(dp[1]) return void(cout<<i);
    }

    cout<<-1<<ln;

}