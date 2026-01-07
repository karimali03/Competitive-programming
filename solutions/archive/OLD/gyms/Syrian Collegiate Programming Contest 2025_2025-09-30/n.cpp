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


struct XorBasis {
    static const int BITS = 22; // use 30 for 1e9 values, 64 for full long long
    long long basis[BITS] = {}; // basis[i] has the vector with i-th bit as the highest set
    int inserted = 0;
    // Insert a number into the basis
    void insert(long long x) {
        inserted++;
        for (int i = BITS - 1; i >= 0; --i) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }

    // Check if a number can be formed from the basis
    bool canMake(long long x) {
        for (int i = BITS - 1; i >= 0; --i) {
            if (x & (1LL << i)) {
                if (!basis[i]) return false;
                x ^= basis[i];
            }
        }
        return true;
    }

  
};


void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    vi num;
    XorBasis st;
    int xr = 0;
    for(int i = 2 ; i < n;  i++){
        xr^=v[i]; st.insert(xr);
    }
    for(int i  = 1 ; i <= 1e5 ; i++){
        if(st.canMake(xr^i)) num.push_back(i);
    }
    cout<<num<<ln;
    while(q--){
        int k; cin>>k; k--;
        if(k >= (int)num.size()) NA;
        else cout<<num[k]<<ln;
    }
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