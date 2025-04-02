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
  
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

void solve(int test_case){
    int n,m; cin>>n>>m;
    vi v(n);
    v.reserve(n);
    vii dp(n, vi(2));

    vii dp(n,vi(2));
    int SQ = sqrt(n) + 1;
    for(int i = n-1;  i >= 0 ; i--){
        if(i+v[i] >= (i/SQ+1)*SQ || i+v[i] >= n ) dp[i] = {1,i};
        else dp[i] = {dp[i+v[i]][0]+1,dp[i+v[i]][1]};
    }
    while(m--){
        int x; cin>>x;
        if(x == 0){
            int a,b; cin>>a>>b; a--; v[a] = b;
            for(int i = a;  i >= (a/SQ)*SQ ; i--){
                if(i+v[i] >= (i/SQ+1)*SQ || i+v[i] >= n ) dp[i] = {1,i};
                else dp[i] = {dp[i+v[i]][0]+1,dp[i+v[i]][1]};
            }
        }else{
            int a; cin>>a; a--;
            int idx = a; int cnt = 0;
            while(idx < n){
                cnt += dp[idx][0];
                a = dp[idx][1] + 1;
                idx = dp[idx][1] + v[dp[idx][1]]; 
            }
            cout<<a<<" "<<cnt<<ln;
        }
    }   
}