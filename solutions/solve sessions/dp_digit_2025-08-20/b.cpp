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



string digits;
pair<int,int> dp[20][2][2][1<<10];
// pos, tight, started, property
int x;
const int mod = 998244353;
int add(int a, int b) {
    return ((a % mod) + (b % mod)) % mod;
}

int mul(int a, int b) {
    return ((a % mod) * (b % mod)) % mod;
}

int fp(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = mul(a,res);
        a = mul(a,a) % mod;
        b/=2;
    }    
    return res;
}    


int val(int pos,int d){
    int pw = (int)digits.size() - pos - 1;
    return mul(fp(10,pw) , d);
}
pair<int,int> rec(int pos, bool tight, bool started, int mask) {
    if (pos == (int)digits.size()) return  {started,0};
    auto &res = dp[pos][tight][started][mask];
    if (~res.first) return res;
    res = {0,0};
    int limit = (tight ? digits[pos] - '0' : 9);

    for (int d = 0; d <= limit; d++) {
        bool newStarted = started || (d != 0);
        if(newStarted && !((mask>>d)&1) && co(mask) == x) continue;
        auto ret = rec(pos+1,tight&&(d==limit),newStarted,newStarted?(mask|(1<<d)):0);
        res.second = add(res.second , add(ret.second , mul(val(pos,d),ret.first)));
        res.first = add(res.first , ret.first);
    }
    return res;
}

void solve(int test_case) {
    int l,r,k; cin>>l>>r>>k;
    digits = to_string(r);
    x = k;
    memset(dp,-1,sizeof(dp));
    auto res = rec(0,1,0,0);
    digits = to_string(l-1);
    memset(dp,-1,sizeof(dp));
    auto res2 = rec(0,1,0,0);
    int ans = (res.second - res2.second + mod)%mod;
    cout<<ans<<ln;
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