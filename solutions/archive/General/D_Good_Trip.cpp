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

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);

template <class T, class V> void _print(pair <T, V> p) {
    cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";
}
template <class T> void _print(vector <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(set <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T> void _print(multiset <T> v) {
    cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";
}
template <class T, class V> void _print(map <T, V> v) {
    cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";
}

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

/*
Problem: Calculate expected sum of friendship values after k random excursions.

Expected Sum = Initial Contribution + Increment Contribution
*/

/*
1) Initial Contribution:
   For each friend pair i with initial value fi:
   - Probability of selecting this pair in one excursion: 1/d
   - Expected contribution after k excursions: (fi / d) * k
   - Total initial contribution (S1):
     S1 = (k * sum(fi)) / d

   Where:
   - d = n*(n-1)/2 (total possible pairs)
   - sum(fi): sum of all friendship values.
*/

/*
2) Increment Contribution:
   When the same pair is selected multiple times:
   - After x times selected: total increment = x*(x-1)/2
   - Number of times selected follows Binomial Distribution:
     P(x) = C(k, x) * (1/d)^x * (1 - 1/d)^(k-x)

3) Shortcut using Binomial Expectation Properties:
   - E[x] = k/d
   - E[x*(x-1)] = k*(k-1)/(d^2)
   - Expected increment for one pair:
     E_increment(i) = (E[x*(x-1)] / 2) = (k*(k-1)) / (2 * d^2)

   Total increment for m friend pairs:
   S2 = m * (k*(k-1)) / (2 * d^2)
*/

/*
Final Answer Formula:
E_total = (k * sum(fi)) / d + m * (k*(k-1)) / (2 * d^2)
*/

// This formula allows O(1) computation per test case after reading input.


const int N = 2'000'005;
const int MOD = 1'000'000'007;
int fact[N],inv_fact[N];

int fp(int x,int y){
    int res = 1;
    while(y > 0){
        if(y&1) res = res * x % MOD;
        x = x * x % MOD;
        y>>=1;
    }
    return res;
}

void INIT(){
    fact[0]  = inv_fact[0] = 1;
    for(int i = 1 ; i < N ; i++) 
    fact[i] = ( i%MOD * fact[i-1]%MOD )% MOD;
    for (int i = 1; i < N; i++) 
    inv_fact[i] = fp(fact[i],MOD-2);
}
 
int nCr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}


void solve(int test_case) {
    int n,m,k; cin>>n>>m>>k;
    vi v(m); cin>>v;
    int res = 0;
    int sum = 0;
    int d = (n*(n-1)/2)%MOD;
    for(int i = 0 ; i < m ;i++) sum+=v[i];
    res = (sum%MOD * k%MOD)%MOD;
    res = (res%MOD * fp(d,MOD-2)%MOD)%MOD;
    for(int i = 1 ; i <= k ; i++){

        int cur = nCr(k,i); 
        cur = (cur%MOD * (i*(i-1)/2)%MOD)%MOD;  
        int a = fp(d,i); int b = fp(d,k-i) , c = fp(d-1,k-i);
        cur = (cur%MOD * fp(a,MOD-2)%MOD)%MOD;   
        cur = ((cur%MOD * c%MOD)%MOD * fp(b,MOD-2)%MOD)%MOD;
        res = (res%MOD + cur%MOD)%MOD;
        cur = (cur%MOD * m%MOD)%MOD;   
    }

    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    INIT();
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}