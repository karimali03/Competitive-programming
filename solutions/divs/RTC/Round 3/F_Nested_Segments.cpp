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

bool cmp(vi & a,vi &b){
    return a[1] > b[1];
}
void solve(int test_case){
    int n; cin>>n;
    set<int>st;
    vii v(n);
    for(int i = 0 ;i  < n ; i++){
        int l,r; cin>>l>>r; v[i] = {l,r,i};
    }   
    sort(all(v),cmp);
    vi suf(n+1); suf[n] = 1e10;
    for(int i = n-1 ; i >= 0 ; i--){
        suf[i] = v[i][0];
        suf[i] = max(suf[i] , suf[i+1]);
    }
    vi res(n);
    int e = 1;
    for(int i = 0 ; i < n ; i++){

    }
    

    
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