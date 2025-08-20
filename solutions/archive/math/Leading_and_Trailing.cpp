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

int pow(int a,int b,int n){
    int res = 1;
    while(b){
        if(b%2 != 0) res = res * a % n;
        a = a*a % n;
        b>>=1;
    }
    return res;
}


void solve(int test_case){
    int n,m; cin>>n>>m;
    int least_3 = pow(n,m,1000);
    // n = m * 1o^x   m -> (0 <= m < 10)  10^x is shift and m is the value
    // n^k = 10^m x 1o^x (0<= m < 1)
    // k * log(n) = x + m  (x int , m float)
    ld x = m * log10(n);
    ld frac = pow(10 , x - floor(x) ) ;
 //   cout<<fixed<<setprecision(5)<<frac<<ln;
    int first_3 = 100.0 * frac;
    cout << first_3 << "..." << setfill('0') << setw(3) << least_3 << endl;
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