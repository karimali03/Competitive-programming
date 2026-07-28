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
    Matrix(){}; 
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
    int n, f1, f2, f3, c; 
    cin >> n >> f1 >> f2 >> f3 >> c;
    
    // Handle base cases directly to avoid negative exponents
    if (n == 1) { cout << f1 % MOD << ln; return; }
    if (n == 2) { cout << f2 % MOD << ln; return; }
    if (n == 3) { cout << f3 % MOD << ln; return; }

    // Safely calculate C^2 % MOD to prevent overflow during matrix multiplication
    int c2 = (c % MOD * c % MOD) % MOD;
    
    Matrix T(4,4);
    T.a[0] = {1, 1, 1, c2};
    T.a[1][0] = 1; // Shift f_x to f_{x-1}
    T.a[2][1] = 1; // Shift f_{x-1} to f_{x-2}
    T.a[3][3] = c2;
    
    Matrix B(4,1);
    B.a[0][0] = f3; 
    B.a[1][0] = f2; 
    B.a[2][0] = f1; 
    B.a[3][0] = 1;
    
    // Apply transition matrix n-3 times
    Matrix ret = expo(T, n - 3) * B;
    
    cout << ret.a[0][0] << ln;
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