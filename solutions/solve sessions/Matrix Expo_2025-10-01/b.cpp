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
   int n; cin>>n;
   vi dp(21); dp[0] = 1;
   for(int i = 1 ; i <= 20 ; i++){
        (dp[i] = ((i-6) >= 0 ? 3*dp[i-6] : 0) + ((i-10) >= 0 ? 3*dp[i-10] : 0) + ((i-14) >= 0 ? 3*dp[i-14] : 0) + ((i-18) >= 0 ? 3*dp[i-18] : 0))%=MOD;
   }
   if(n <= 20){
       int sum = 0;
       for(int i = max(0ll,n-19) ; i <= n ; i++) (sum+=dp[i])%=MOD;
       cout<<sum<<ln; return;
   }
   Matrix single(20,20);
   for(int i = 5 ; i < 20 ; i+=4) single.a[0][i] = 3;
   for(int i = 1 ; i < 20; i++) single.a[i][i-1] = 1;
   auto ans = expo(single,n-19);
   Matrix base(20,1);
   for(int i = 0 ; i < 20;  i++) base.a[i][0] = dp[19-i];
   auto ret = ans * base;
   int sum = 0;
   for(int i = 0 ; i < 20 ; i++) (sum+=ret.a[i][0])%=MOD;
   cout<<sum<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}