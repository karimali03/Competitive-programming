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

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

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

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

void solve(int test_case){
    int n; cin>>n;
    vi v(n); cin>>v;
    vi suf(n);
    for(int  i = n-1;  i>= 0 ; i--){
        suf[i] = v[i];
        if(i+1<n) suf[i]^=suf[i+1];
    }
    int x = suf[0];
    int j = 0;
    int xr = 0;
    while (j < n && xr != x) xr^=v[j++];
    if(xr == x){
        xr = 0;
        while (j < n && xr !=x) xr^=v[j++];
    }
    if(j < n && xr == suf[j]) return void(cout<<"YES"<<ln);
  
    if(suf[0] == 0){
        for(int i = 0 ; i <  n; i++){
            x = v[i];
             xr = 0;  j = 0;
            while(j < n && xr != x) xr^=v[j++];
            if(j < n && xr == suf[j]) return void(cout<<"YES"<<ln);
        }
    }
    else cout<<"NO"<<ln;
}