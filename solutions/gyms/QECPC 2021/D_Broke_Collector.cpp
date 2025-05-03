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

vi v;
vii dp;
int n;
int MX = 0;
map<pair<int,int>,int>mp;
int rec(int i,int c){
    if(c > MX ) return 0;
    int &ret = dp[i][c];
    if(~ret) return ret;
    ret = mp.count({v[i],c}) ? mp[{v[i],c}] : 0;
    int mx = rec(i,c+1);
    if(i+1 < n){
        mx = max ( mx , rec(i+1,c+abs(v[i]-v[i+1])) );
    }
    if(i-1 >= 0){
        mx = max ( mx , rec(i-1,c+abs(v[i]-v[i-1])) );
    }
 //   cout<< v[i] << " " << c << " "<< ret  +mx<<ln;
    return ret = ret +  mx;
}

void solve(int test_case){
   cin>>n;
   v = vi(n);
   MX = 0; mp.clear();
   f(i,0,n){
       int x,y,z; cin>>x>>y>>z;
       v[i] = x;
       mp[{x,y-1}] += z;
       MX = max(MX , y);
    }

    dp = vii(n+1,vi(MX+1,-1));

    sort(all(v));
    v.erase(unique(v.begin(), v.end()), v.end()); 
    n = v.size();
    int mx = 0;
    for(int i = 0 ; i < n ; i++){
        mx = max(mx , rec(i,0));
    }
    cout<<mx<<ln;
}

signed main() {
    freopen("collector.in", "r", stdin);  // Redirects standard input to read from "input.txt"

    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}