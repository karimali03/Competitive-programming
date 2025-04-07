#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

void solve(int test_case);

const int P = 41;
// safe_primes = {31, 37, 41, 53, 59, 67, 71, 79, 89, 97}; 
const int M = 1e9 + 9;
const int MAXN = 1e6 + 5;
int p_pow[MAXN], inv_p_pow[MAXN];

// Fast modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Precompute powers and inverses
void precompute_hashing() {
    p_pow[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p_pow[i] = p_pow[i - 1] * P % M;
    }
    for (int i = 0; i < MAXN; i++) {
        inv_p_pow[i] = mod_pow(p_pow[i], M - 2, M);
    }
}


struct StringHasher {
    vector<long long> hash;

    StringHasher(const string &s) {
        int n = s.size();
        hash.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * p_pow[i]) % M;
        }
    }

    long long get_hash(int l, int r) {
        long long h = (hash[r + 1] - hash[l] + M) % M;
        return h * inv_p_pow[l] % M;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    precompute_hashing();
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}



void solve(int test_case){
    if(test_case != 1) cout<<ln;
    string a,b; cin>>a>>b;
    int n = a.size();
    int m = b.size();
    if(m > n) return void(cout<<"Not Found\n");
    StringHasher sha(a),shb(b);
    vi cnt;
    for(int i = 0 ; i <= n-m ; i++){
        if(sha.get_hash(i,i+m-1) == shb.get_hash(0,m-1)) cnt.push_back(i);
    }
    if(!cnt.empty()){
        cout<<cnt.size()<<ln;
        for(auto it : cnt) cout<<it+1<<" ";
        cout<<ln;
    }
    else{
        cout<<"Not Found\n";
    }
}