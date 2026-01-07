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

struct d {
    int aud;
    vi b;
    d(int p = 0):b(p){};
    bool operator < (const d& rhs) const {
        return aud < rhs.aud;
    }
};
const int N = 100005;
int dp[N][1<<7];
d v[N];
int pre[N];
int n,p,k;

int rec(int i,int mask){
     int &ret = dp[i][mask];
     if(~ret) return ret;
      
      int rem = max(0ll , k - i + co(mask));
        if(co(mask) == p){
            ret = pre[i+rem-1] - (i ? pre[i-1] : 0);
            return ret;
        }
     
        ret = 0;
        int last = p - co(mask) + max(0ll,rem-1);
        if(n-i-1 >= last)
        ret = (rem > 0 ? v[i].aud: 0) + rec(i+1,mask);
        for(int j = 0 ; j  < p ; j++){
            if((mask>>j)&1) continue;
            ret = max(ret , v[i].b[j] + rec(i+1,(mask|(1<<j))) );
        }
        return ret;
}
void solve(int test_case) {
    cin>>n>>p>>k;
    for(int i = 0 ;i < n ; i++) cin>>v[i].aud;
    for(int i = 0 ;i < n ; i++){
        v[i].b = vi(p);
        cin>>v[i].b;
    }
    sort(v,v+n);
    reverse(v,v+n);
    pre[0] = v[0].aud;
    for(int i = 1 ; i < n ; i++) pre[i] = pre[i-1] + v[i].aud;
    memset(dp,-1,sizeof(dp));
   
    cout<<rec(0,0)<<ln;
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