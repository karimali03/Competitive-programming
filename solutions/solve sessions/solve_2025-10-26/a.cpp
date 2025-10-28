#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>

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
const int N = 10;
bool vld[N]; 

struct Matrix {
    int rows, cols;
    vector<vector<int>> a;

    Matrix() = default;

    Matrix(int r, int c) : rows(r), cols(c), a(r, vector<int>(c, 0)) {}
 
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
 
Matrix expo(Matrix x, int k){
    Matrix ret(x.rows,x.cols);
    f(i,0,x.rows) ret.a[i][i] = 1;
    while(k > 0){
        if(k & 1) ret = ret * x;
        x = x * x;  k>>=1;
    }
    return ret;
}

int dp_digit_div_x(int b,int x){
    if (b < 0) return 0;

    Matrix single(x,x);
    for(int i = 0 ; i < x ; i++){
        for(int d = 0; d < N ; d++) {
            if(vld[d]){
                int nxt_mod = (i*10+d)%x;
                single.a[i][nxt_mod] = (single.a[i][nxt_mod] + 1) % MOD;
            }
        }
    }
    
    Matrix res = expo(single, b);

    Matrix base(1, x);
    for(int d = 1 ; d < N ; d++) {
        if(vld[d]){
            int r = d % x;
            base.a[0][r] = (base.a[0][r] + 1) % MOD;
        }
    }
    
    auto ans = base * res;

    return ans.a[0][0];
}

void solve(int test_case) {
    int b, x, forbidden_count; 
    cin >> b >> x >> forbidden_count;
    
    for(int i=0; i<N; ++i) vld[i] = true;
    for(int i=0; i<forbidden_count; ++i) {
        int fd;
        cin >> fd;
        vld[fd] = false;
    }
    
    int result = dp_digit_div_x(b, x);
    
    cout << result << ln;
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