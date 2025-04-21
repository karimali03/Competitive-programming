#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define vii vector<vector<vector<int>>>
#define f(i,a,b) for(int i=a;i<b;i++)
#define f(i,n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define PI acos(-1)
#define print(vec,n) for(int i = 0; i < n && cout<<v[i]<<" "; i++);cout<<"\n";
#define print(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

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
        if(b&1) res = res * a % n;
        a = a*a % n;
        b>>=1;
    }
    return res;
}


void solve(int test_case){
    int a,b,n; cin>>a>>b>>n;
    cout<<pow(a,b,n)<<ln;
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
