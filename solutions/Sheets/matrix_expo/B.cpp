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
const int PHI = 1e9+6;
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
                    (ret.a[i][j] += a[i][k] * other.a[k][j])%=PHI;
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

int expo(int x,int k){
    int ret = 1;
    x%=MOD;
    while(k > 0){
        if(k & 1) ret = (ret * x)%MOD;
        x = (x * x)%MOD;  k>>=1;
    }
    return ret;
}

void solve(int test_case) {
    int n,f1,f2,f3,c; cin>>n>>f1>>f2>>f3>>c;
    Matrix T(5,5);
    T.a[0] = {1,1,1,1,0};
    T.a[1] = {1,0,0,0,0};
    T.a[2] = {0,1,0,0,0};
    T.a[3] = {0,0,0,1,2};
    T.a[4] = {0,0,0,0,1};
    T = expo(T,n-3);
    int p3 = T.a[0][0];
    int p2 = T.a[0][1];
    int p1 = T.a[0][2];
    int pc = (T.a[0][3] * 2 + T.a[0][4]) % PHI;
    int ans = 1;
    (ans *= expo(f1,p1))%=MOD;
    (ans *= expo(f2,p2))%=MOD;
    (ans *= expo(f3,p3))%=MOD;
    (ans *= expo(c,pc))%=MOD;
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}