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

using mat = vec<vec<ll>>;
const int mod = 1'000'000'007;
mat product(const mat& a, const mat& b) {
    int n = a.size(), m = b[0].size(), p = b.size();
    mat ret(n, vi(m, 0));
    for(int i = 0 ;i < n ; i++){
        for(int k = 0 ;k < p ; k++){
            ll aik = a[i][k] % mod; 
            if (aik == 0) continue;
            for(int j =0 ;j < m ; j++){
                ret[i][j] += aik * b[k][j];
                if (ret[i][j] >= mod) ret[i][j] %= mod; 
            }
        }
    }
    return ret;
}

mat expo(mat &a , int k){
    int n = a.size();
    mat res(n,vi(n));
    for(int i = 0 ; i  < n ; i++) res[i][i] = 1; // identity matrix
    while(k>0){
        if(k&1) res = product(res,a);
        a = product(a,a);
        k>>=1;
    }
    return res;
}

int conv(char ch){
    if(ch <= 'Z') return 26 + ch-'A';
    return  ch-'a';
}
void solve(int test_case){
    int n,m,k; cin>>n>>m>>k;
    mat mx(m,vi(m,1));
    for(int i = 0 ; i < k ; i++){
        char a,b; cin>>a>>b;
        mx[conv(a)][conv(b)] = 0;
    }
    mat v(m,vi(1,1));
    auto ex = expo(mx,n-1);
    auto res = product ( ex , v  ) ;
    int sum = 0;
    for(auto it : res) sum= (sum%mod + it[0]%mod)%mod;
    cout<<sum<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}