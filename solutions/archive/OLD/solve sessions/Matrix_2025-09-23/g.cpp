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

const int MOD = 1e9+7;
struct Matrix {
    int rows, cols;
    vector<vector<int>> a;
 
    Matrix(int r, int c) : rows(r), cols(c), a(r, vector<int>(c)) {}
 
    Matrix operator*(const Matrix &other) const {
        assert(cols == other.rows); 
        Matrix ret(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int k = 0; k < cols; k++) {
                for (int j = 0; j < other.cols; j++) {
                    (ret.a[i][j] += a[i][k] * other.a[k][j])%=MOD;
                }
            }
        }
        return ret;
    }
};
 
Matrix expo(Matrix &x,int k){
    Matrix ret(x.rows,x.cols);
    f(i,0,x.rows) ret.a[i][i] = 1;
    while(k > 0){
        if(k & 1) ret = ret * x;
        x = x * x;  k>>=1;
    }
    return ret;
}

void solve(int test_case) {
    int n,k; cin>>n>>k; 
    vi v(n); cin>>v;
    vi c(n); cin>>c;
    int p,q,r; cin>>p>>q>>r;
    if(k < n){
        cout<<v[k]<<ln;
        return;
    }
    Matrix single(n+3,n+3);
    for(int i = 0; i < n ; i++) single.a[0][i] = c[i]; // nth term
    single.a[0][n] = p; single.a[0][n+1] = q; single.a[0][n+2] = r; // p + i*q + i^2 * r; 
    for(int i = 1 ; i < n ; i++) single.a[i][i-1] = 1; // every term take pev
    single.a[n][n] = 1; // constant 1
    single.a[n+1][n] = 1; single.a[n+1][n+1] = 1;  // i = 1 + i
    single.a[n+2][n+2] = 1; single.a[n+2][n] = 1; single.a[n+2][n+1] = 2; // (i+1)^2 = i^2 + 1 + 2i
    auto ans = expo(single,k-n+1);
    Matrix base(n+3,1);
    for(int i = 0 ; i < n ; i++) base.a[i][0] = v[n-i-1];
    base.a[n][0] = 1; base.a[n+1][0] = n;
    base.a[n+2][0] = n*n;
    auto res = ans * base;
    cout<<res.a[0];
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