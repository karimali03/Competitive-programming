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

const int mod = 1e9+7;
struct Matrix {
    ll a[2][2];
    Matrix() {
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix c;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % mod;
                }
            }
        }
        return c;
    }
};


Matrix matrixpower(Matrix a, ll n) {
    Matrix res;
    for (int i = 0; i < 2; i++) res.a[i][i] = 1;
    
    while (n) {
        if (n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

const int N = 1000005;
int fib[N];

void solve(int test_case) {
    int m; cin>>m;
    
    Matrix res;
    Matrix base;
    base.a[0][0] = 1 , base.a[0][1] = 1;
    base.a[1][0] = 1;
    while(m--){
        int a,b; cin>>a>>b;
        if(a == 1){
            (res.a[0][0] += fib[b])%=mod;
            (res.a[1][0] += fib[b-1])%=mod;
        }else{
            
            Matrix x = matrixpower(base , b);
            res = x * res;
        }
        cout<<res.a[0][0]<<ln;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   // freopen("fib.in", "r", stdin);
    fib[1] = 1,fib[2] = 1;
    for(int i = 3 ; i < N ; i++){
        fib[i] = (fib[i-1] + fib[i-2])%mod;
    }
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}