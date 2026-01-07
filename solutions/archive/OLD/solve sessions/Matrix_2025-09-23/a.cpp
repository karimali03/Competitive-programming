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

struct Matrix {
    int rows, cols;
    vector<vector<double>> a;

    Matrix(int r, int c) : rows(r), cols(c), a(r, vector<double>(c, 0)) {}

    Matrix operator*(const Matrix &other) const {
        assert(cols == other.rows); // Valid multiplication
        Matrix ret(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    ret.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return ret;
    }
};

Matrix expo(Matrix &x,int k){
    Matrix ret(2,2);
    f(i,0,2) ret.a[i][i] = 1.0;
    while(k > 0){
        if(k & 1) ret = ret * x;
        x = x * x;
        k/=2;
    }
    return ret;
}

void solve(int test_case) {
    /*
     dp[happy] = (1 - p) dp[happy] + p * dp[sad]
     dp[sad] = p dp[happy]+  (1 - p) dp[sad]
     dp[0][1] = p , dp[0][0] = (1 - p)
     dp[1][0] = p , dp[1][1] = (1 - p)
    */
    int n; cin>>n;
    double p; cin>>p;
    Matrix single(2, 2);
    single.a[0][0] = single.a[1][1] = (1 - p);
    single.a[0][1] = single.a[1][0] = p;
    auto ans = expo(single , n);
    cout<<fixed<<setprecision(6)<<ans.a[0][0]<<ln;
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