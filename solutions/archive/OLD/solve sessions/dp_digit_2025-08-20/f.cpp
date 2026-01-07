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


string a,b;
ll dp[20][2][2][2];
// pos, tight left, tight right ,started, property
// 0 , 1 , 1 , 0 , ----
ll rec(int pos, bool tl,bool tr,bool st) {
    if (pos == (int)b.size()) return 1;
    ll &ret = dp[pos][tl][tr][st];
    if (~ret) return ret;
    ret = 0;

    int l = (tl ? a[pos] - '0' : 0);
    int r = (tr ? b[pos] - '0' : 9);
    for (int d = l; d <= r; d++) {
        bool ns = st || (d != 0);
        ret = max(ret , rec(pos + 1, tl && (d == l), ns , tr && (d == r)));
    }
    return ret;
}

int dp_digit(int l,int r){
    a = to_string(l);
    b = to_string(r);
    while (a.size() < b.size()) a = '0' + a;
    memset(dp,-1,sizeof(dp));
    return rec(0,1,1,0);
}

void solve(int test_case) {
    cin>>a>>b;
    while (a.size() < b.size()) a = '0' + a;
    memset(dp,-1,sizeof(dp));
    string res;
    function<void(int,bool,bool,bool)> build = [&](int pos,bool tight,bool started,bool tight2){
        if (pos == (int)b.size()) return ;
        int opt = rec(pos,tight,started,tight2);
        int r = (tight ? b[pos] - '0' : 9);
        int l = (tight2 ? a[pos] - '0' : 0);
        for (int d = l; d <= r; d++) {
            bool newStarted = started || (d != 0);
            int val = (newStarted ? d : 1) * rec(pos + 1, tight && (d == r), newStarted , tight2 && (d == l));
            if(opt == val){
                res.push_back(d+'0');
                build(pos + 1, tight && (d == r), newStarted , tight2 && (d == l));
                return;
            }
        }
    };
    build(0,1,0,1);
    reverse(all(res));
    while (res.back() == '0') res.pop_back();
    reverse(all(res));
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