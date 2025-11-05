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


// Constants
const int MAXN = 2e5 + 5;
const int M1 = 1e9 + 7, M2 = 1e9 + 9;
int P1,P2;

// Precomputed arrays
int p_pow1[MAXN], inv_p_pow1[MAXN];
int p_pow2[MAXN], inv_p_pow2[MAXN];

// Modular exponentiation (Fermat's little theorem for inverse)
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

pair<int,int> one[MAXN]{},zero[MAXN]{};
void INIT() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist1(256, M1 - 2);  // avoid very small or large bases
    uniform_int_distribution<int> dist2(256, M2 - 2);

    P1 = dist1(rng);
    P2 = dist2(rng);

    p_pow1[0] = p_pow2[0] = 1;
    one[1] = {3, 3};
    zero[1] = {2, 2};

    for (int i = 1; i < MAXN; i++) {
        p_pow1[i] = p_pow1[i - 1] * P1 % M1;
        p_pow2[i] = p_pow2[i - 1] * P2 % M2;
    }

    for (int i = 2; i < MAXN; i++) {
        zero[i] = {(zero[i - 1].first + 2 * p_pow1[i - 1]) % M1,
                   (zero[i - 1].second + 2 * p_pow2[i - 1]) % M2};
        one[i] = {(one[i - 1].first + 3 * p_pow1[i - 1]) % M1,
                  (one[i - 1].second + 3 * p_pow2[i - 1]) % M2};
    }

    for (int i = 0; i < MAXN; i++) {
        inv_p_pow1[i] = mod_pow(p_pow1[i], M1 - 2, M1);
        inv_p_pow2[i] = mod_pow(p_pow2[i], M2 - 2, M2);
    }
}

// Double Hashing Struct
struct DoubleHasher {
    vector<long long> hash1, hash2;

    DoubleHasher(const string &s) {
        int n = s.size();
        hash1.resize(n + 1, 0);
        hash2.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] + (s[i] - '0' + 2) * p_pow1[i]) % M1;
            hash2[i + 1] = (hash2[i] + (s[i] - '0' + 2) * p_pow2[i]) % M2;
        }
    }

    // Get hash of substring [l..r]
    pair<long long, long long> get_hash(int l, int r) {
        if(l > r) return {0,0};
        long long h1 = (hash1[r + 1] - hash1[l] + M1) % M1;
        h1 = h1 * inv_p_pow1[l] % M1;

        long long h2 = (hash2[r + 1] - hash2[l] + M2) % M2;
        h2 = h2 * inv_p_pow2[l] % M2;

        return {h1, h2};
    }
};




void solve(int test_case) {
    int n,m; cin>>n>>m;
    string s; cin>>s;
    set<pair<int,int>>st;
    DoubleHasher sh(s);
    vi cnt(n);
    cnt[0] = ( s[0] == '1' );
    f(i,1,n) cnt[i] = cnt[i-1] + (s[i] == '1');
    for(int i = 0;i < m ; i++){
        int l,r; cin>>l>>r; l--,r--;
        pair<int,int> hash = sh.get_hash(0,l-1);
        int on = cnt[r] - (l ? cnt[l-1] : 0);
        int ze = (r-l+1) - on;
        (hash.first += (zero[ze].first * p_pow1[l])%M1)%=M1;
        (hash.second += (zero[ze].second * p_pow2[l])%M2)%=M2;
        (hash.first += (one[on].first * p_pow1[l+ze])%M1)%=M1;
        (hash.second += (one[on].second * p_pow2[l+ze])%M2)%=M2;
        (hash.first += ( sh.get_hash(r+1,n-1).first * p_pow1[r+1])%M1)%=M1;
        (hash.second += ( sh.get_hash(r+1,n-1).second * p_pow2[r+1])%M2)%=M2;
        st.insert(hash);
      //  cout<<hash.first<<ln;
    }
    cout<<st.size()<<ln;
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