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
    int n,k,z; cin>>n>>k>>z;
    vi v(n); cin>>v;
    int res = 0;
    for(int i = 0 ; i <=  z ; i++){
        int mx = k - i*2;
        if(mx < 0) continue;
        int mxe = 0; int mxi = 0;
        for(int j = 0 ; j <= min(mx,n-2) ; j++){
            if(v[j]+v[j+1] >= mxe) mxe = v[j]+v[j+1],mxi=j;
        }
        int sum = v[0];
        int kk = k;
        for(int j = 1 ; j <= mxi ; j++) sum+=v[j],kk--;

        sum += (v[mxi]+v[mxi+1]) * i;

        kk-=i*2;

        for(int j = mxi+1 ; kk > 0 && j < n ; kk--,j++) sum+=v[j];
        res = max(res , sum);
    }
    cout<<res<<ln;
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