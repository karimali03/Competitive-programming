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




// Constants
const int MAXN = 2e5 + 5;
const int M1 = 1e9 + 7, M2 = 1e9 + 9;
const int P1 = 54, P2 = 37;

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

// Precompute powers and modular inverses
void INIT() {
    p_pow1[0] = p_pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p_pow1[i] = p_pow1[i - 1] * P1 % M1;
        p_pow2[i] = p_pow2[i - 1] * P2 % M2;
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
            hash1[i + 1] = (hash1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % M1;
            hash2[i + 1] = (hash2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % M2;
        }
    }
    
    // Get hash of substring [l..r]
    pair<long long, long long> get_hash(int l, int r) {
        long long h1 = (hash1[r + 1] - hash1[l] + M1) % M1;
        h1 = h1 * inv_p_pow1[l] % M1;
        
        long long h2 = (hash2[r + 1] - hash2[l] + M2) % M2;
        h2 = h2 * inv_p_pow2[l] % M2;
        
        return {h1, h2};
    }
};

void dfs(int v, int p, vector<vector<int>> &adj, vector<int> &in, vector<int> &out, int &timer, string &s) {
    in[v] = timer++;
    s.push_back('(');
    for (auto it : adj[v]) {
        if (it == p) continue;
        dfs(it, v, adj, in, out, timer, s);
    }
    s.push_back(')');
    out[v] = timer++;
}

void solve(int test_case) {
    int n; cin >> n;

    vector<vector<int>> adj0(n);  // Tree A
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        for (int j = 0; j < x; j++) {
            int a; cin >> a; a--;
            adj0[i].push_back(a);
        }
    }

    int m; cin >> m;
    vector<vector<int>> adj1(m);  // Tree B
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        for (int j = 0; j < x; j++) {
            int a; cin >> a; a--;
            adj1[i].push_back(a);
        }
    }

    vector<int> in0(n), out0(n), in1(m), out1(m);
    int timer = 0;
    string a;
    dfs(0, -1, adj0, in0, out0, timer, a);

    timer = 0;
    string b;
    dfs(0, -1, adj1, in1, out1, timer, b);

    DoubleHasher sa(a), sb(b);
    map<pair<int, int>, int> mpa, mpb;

    for (int i = 1; i < n; i++) {
        mpa[sa.get_hash(in0[i], out0[i])]++;
    }

    for (int i = 0; i < m; i++) {
        mpb[sb.get_hash(in1[i], out1[i])]++;
    }

    int res = 1;
    for (auto &it : mpb) {
        res += 2 * n - 1 - mpa[it.first];
    }
    cout << res << ln;
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