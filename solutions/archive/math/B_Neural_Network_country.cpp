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
            for(int j = 0 ;j < m ; j++){
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

void solve(int test_case){
    int n,l,m; cin>>n>>l>>m;
    vii v(3,vi(n));
    for(int i = 0 ; i < 3 ; i++) cin>>v[i];
    mat v1(m,vi(m));
    vi cnt(m+1); 
    f(i,0,n) cnt[v[0][i]%m]++;
    for(int i = 0 ; i < m ; i++){
        for(int j  = 0 ; j < m ; j++){
            v1[i][j] += cnt[( i - j + m)%m];
        }
    }
    mat v2(m,vi(m));
    cnt = vi(m+1);
    f(i,0,n) cnt[v[1][i]%m]++;
    for(int i = 0 ; i < m ; i++){
        for(int j  = 0 ; j < m ; j++){
            v2[i][j] += cnt[( i - j + m)%m];
        }
    }
    mat v3(m,vi(m));
    cnt = vi(m+1);
    f(i,0,n) cnt[ (v[2][i] + v[1][i])%m]++;
    for(int i = 0 ; i < m ; i++){
        for(int j  = 0 ; j < m ; j++){
            v3[i][j] += cnt[( i - j + m)%m];
        }
    }

    auto res = product(v1,product(expo(v2,l-2),v3));
    cout<<res[0][0]<<ln;


}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}