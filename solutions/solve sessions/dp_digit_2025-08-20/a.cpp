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
ll dp[12][2][2][25205][10];
// pos, tight, started, property
int x;
ll rec(int pos, bool tight, bool started, int lm,int prv) {
    if (pos == (int)digits.size()){
        if(prv != 0) lm = lcm(lm,prv);
        return (lm == x && started);
    } 
    ll &res = dp[pos][tight][started][lm][prv];
    if (~res) return res;
    res = 0;
    int limit = (tight ? digits[pos] - '0' : 9);

    for (int d = 0; d <= limit; d++) {
        bool newStarted = started || (d != 0);
        if(started && prv == 0 && d == 0) continue;
        int new_lm = lm;
        if(started){
            new_lm = prv == 0 ? lm : lcm(lm , prv);
            if(d == 0) new_lm = lcm(lm , prv*10);
        }
        res += rec(pos + 1,
                       tight && (d == limit),
                       newStarted,
                       new_lm,d);
    }
    return res;
}

void solve(int test_case) {
    int l,r,k; cin>>l>>r>>k;
    if(k > 25200){
        cout<<0<<ln;
        return;
    }
 
    memset(dp,-1,sizeof(dp));
    digits = to_string(r);
    x = k;
    int res = rec(0,1,0,1,0);
   
    digits = to_string(l-1);
    memset(dp,-1,sizeof(dp));
    res-= rec(0,1,0,1,0);
    cout<<res<<ln;
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
