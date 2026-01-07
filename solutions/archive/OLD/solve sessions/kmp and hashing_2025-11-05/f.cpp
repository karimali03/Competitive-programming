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


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct PairHash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
        // A common way to combine two hashes
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        
        // This is a simple and effective combination
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

#define int long long


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll BASE[2];
int MOD[2];
int cnt[2]{};




gp_hash_table<pair<int,int>,int,PairHash> hval[2];
ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int get(pair<int,int> x,int idx) {
    if (hval[idx].find(x) != hval[idx].end()) return hval[idx][x];
    return hval[idx][x] = mod_pow(BASE[idx], cnt[idx]++, MOD[idx]);
}

struct MultisetHashing {
    vector<int> h;
    int n,idx;
    MultisetHashing(vector<pair<int,int>> &v,int idx):idx(idx) {
        n = v.size();
        h = vector<int>(n + 1);
        for (int i = 0; i < n; i++) {
            (h[i + 1] =  get(v[i],idx) + h[i])%=MOD[idx];
        }
    }
    // zero based
    int get_hash(int l, int r) {
        int ret = h[r+1] - h[l] + MOD[idx];
        return ret % MOD[idx];
    }
};


void solve(int test_case) {
    int n; cin>>n;
    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].first>>v[i].second;
        if(v[i].first > v[i].second) swap(v[i].first,v[i].second);
    }
    MultisetHashing sh(v,0),sh2(v,1);
   
    gp_hash_table<pair<int,int>, int , PairHash> mp;
 
    for(int i = 0;i < n ; i++){
        for(int j = i; j < n ; j++){
            mp[{sh.get_hash(i,j),sh2.get_hash(i,j)}]++;
        }
    }
    int res = 0;
    for(auto &[a,b] : mp) res += (b*(b-1))/2;
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    BASE[0] = uniform_int_distribution<ll>(4000005, 40000005)(rng) | 1; 
    BASE[1] = uniform_int_distribution<ll>(4000005, 40000005)(rng) | 1; 
    MOD[0] = 1e9+7; MOD[1] = 1e9+9;
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}