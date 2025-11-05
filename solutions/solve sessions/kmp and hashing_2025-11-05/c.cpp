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


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
map<ll,ll> hval;
ll get(ll x) {
    if(hval.count(x)) return hval[x];
    return hval[x] = rng();
}

struct XorHashing {
    vector<int> h;
    int n;
    XorHashing(vector<int> &v) {
        n = v.size();
        h = vector<ll>(n + 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] =  get(v[i]) ^ h[i];
        }
    }
    // zero based
    ll get_hash(int l, int r) {
        return h[r+1] ^ h[l];
    }
};


void solve(int tc){
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    XorHashing st(v);
    while(q--){
        int l,r; cin>>l>>r;
        if(st.get_hash(l,r) == 0) YES;
        else NO;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}