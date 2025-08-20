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


int dp[1<<7];
struct d {
    int aud;
    vi b;
    d(int p = 0):b(p){};
    bool operator < (const d& rhs) const {
        return aud < rhs.aud;
    }
};
void solve(int test_case) {
    int n,p,k; cin>>n>>p>>k;
    vector<d>v(n);
    for(int i = 0 ;i < n ; i++) cin>>v[i].aud;
    for(int i = 0 ;i < n ; i++){
         v[i].b = vi(p);
         cin>>v[i].b;
    }
    sort(rall(v));
    vector<int>used(n);
    vector<int>cur;
    int mx = 0;
    function<int(int)> rec = [&](int mask) -> int{
        if(co(mask) == p) return 0;
        int &ret = dp[mask];
        if(~ret) return ret;
        ret = 0;
        int c = co(mask);
        for(int i = 0 ;i < p ; i++){
            if((mask>>i)&1) continue;
            ret = max(ret , v[cur[i]].b[c] + rec((mask | (1<<i))) );
        }
        return ret;
    };
    function<void(ll,ll)> calc = [&](ll idx, ll rem) -> void {
        if(rem == 0){
            int cnt = 0;
            int sum = 0;
            for(int i = 0 ; i < n && cnt < k ; i++){
                if(!used[i]) sum+=v[i].aud,cnt++;
            }
            memset(dp,-1,sizeof(dp));
            mx = max(mx ,  sum + rec(0) ) ;
        }
        if(idx == n) return;
        used[idx] = 1;
        cur.push_back(idx);
        calc(idx+1,rem-1);
        used[idx] = 0;
        cur.pop_back();
        calc(idx+1,rem);
     };
     calc(0,p);
     cout<<mx<<ln;
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