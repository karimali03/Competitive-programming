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

int rec(vii & v , vi &cost , int n){
    vii dp(n,vi(2,1e18));
    dp[0][0] = 0; dp[0][1] = cost[0];
    for(int i = 1 ; i < n ; i++){
        for(int x = 0 ; x < 2 ; x++){
            for(int y = 0 ;  y < 2 ; y++){
                bool valid = true;
                for(int j = 0 ;j < n ; j++) valid&=(v[i-1][j]+y != v[i][j]+x);
                if(valid){
                    dp[i][x] = min(dp[i][x] , dp[i-1][y] + (x?cost[i]:0) );
                }
            }
        }
    }
    return min(dp[n-1][0],dp[n-1][1]);
}


void trans(vii & v ,int n){
    for(int i  = 0 ; i <  n; i++){
        for(int j = i+1 ; j <  n;  j++){
            swap(v[i][j],v[j][i]);
        }
    }
}

void solve(int test_case){
    int n; cin>>n;
    vii v(n,vi(n));
    f(i,0,n) cin>>v[i];
    vi a(n),b(n); cin>>a>>b;
    int c1 = rec(v,a,n);
    trans(v,n);
    int c2 = rec(v,b,n);
    if(c1 == 1e18 || c2 == 1e18) cout<<-1<<ln;
    else cout<<c1+c2<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}