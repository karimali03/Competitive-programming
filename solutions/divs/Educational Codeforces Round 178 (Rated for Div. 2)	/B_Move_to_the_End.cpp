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

void solve(int test_case){
    int n; cin>>n;
    vi v(n); cin>>v;
    vi suf(n);
    vi mx(n);
    for(int i = n-1 ; i >= 0 ; i--){
        suf[i] = v[i];
        if(i!=n-1) suf[i]+=suf[i+1];
    }   
    for(int i = 0 ;i  < n ; i++){
        mx[i] = v[i];
        if(i) mx[i] = max(mx[i],mx[i-1]);
    }
    for(int i = n-1 ; i >= 0 ; i--){
        if(i != 0 && mx[i-1] > v[i]){
            cout<<suf[i]-v[i]+mx[i-1]<<" ";
        }
        else cout<<suf[i]<<" ";
    }
    cout<<ln;

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