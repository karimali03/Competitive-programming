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
    int n,k; cin>>n>>k;
    string s; cin>>s;
    vii v(k,vi(26));
    for(int i = 0 ; i < k ; i++){
        for(int j = i ; j < n ; j+=k){
            v[i][s[j]-'a']++;
        }
    }
    int res = 0;
    for(int i = 0 ; i < (k+1)/2 ; i++){
        int mx = 0,sum=0;
        for(int x = 0 ; x < 26 ; x++){
            int sx = v[i][x] + (i!=k-i-1?v[k-i-1][x]:0);
        //    if(sx) cout<<x<<" "<<sx<<ln;
            sum+=sx; mx = max(mx,sx);
        }
    //    cout<<sum<<" "<<mx<<ln;
        res+=(sum-mx);
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