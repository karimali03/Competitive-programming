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

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

const long long RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();

struct chash {
    const uint64_t C = (long long)(4e18 * acos(0)) | 71;
    
    // Hash for integers
    long long operator()(long long x) const {
        return __builtin_bswap64((x ^ RANDOM) * C);
    }

    // Hash for pairs
    template<typename T, typename U>
    long long operator()(pair<T, U> x) const {
        return operator()(x.first) ^ operator()(x.second);
    }
};

gp_hash_table<pair<int, int>, ll, chash> mp;


int n,k; 
vec<ll> cold,hot;
vi v;


ll rec(int cur,int prv){
    if(cur == n-1 || cur == n) return 0;
    if(mp.find({cur,prv}) != mp.end()) return mp[{cur,prv}];
    ll ans = (v[cur] == v[cur+1] ? hot[v[cur+1]-1] : cold[v[cur+1]-1])
    + rec(cur+1,prv);
    ll ac = (prv == v[cur+1] ? hot[v[cur+1]-1] : cold[v[cur+1]-1]);
    int pv = cur+1;
    for(int i = cur+2 ; i < n ; i++){
        int val = (v[cur] == v[i] ? hot[v[i]-1] : cold[v[i]-1]);
        ans = min(ans , rec(i,v[i-1]) + ac + val);
        if(v[i] == v[pv]) ac+=hot[v[i]-1];
        else ac+=cold[v[i]-1];
        pv = i;
    }
    ans = min(ans , ac);
    return mp[{cur,prv}] = ans;
}
void solve(int test_case) {
        mp.clear();
        cin>>n>>k;
        v = vi(n);
        cold = hot = vec<ll>(k);
        cin>>v>>cold>>hot;

  cout<<rec(0,0)+cold[v[0]-1]<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}