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
// get divisors of n
vector<int>di;
vii divisiors(int n){ // O( sqrt(n) )
    vii res;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            res.push_back({i,n/i});
            di.push_back(i); 
            if(i!=n/i) di.push_back(n/i);
        }
    }
    return res;
}

void solve(int test_case){
    int n,m,k; cin>>n>>m>>k;
    vi a(n),b(m); cin>>a>>b;
    auto res = divisiors(k);
    map<int,int>ma,mb;
    for(int i  = 0 ; i < n ; i++){
        int cnt = 0;
        while(i < n  && a[i] == 1) cnt++,i++;
        for(auto x : di){
            ma[x]+=(cnt-x+1>0?cnt-x+1:0);
        }
    }
    for(int i  = 0 ; i < m ; i++){
        int cnt = 0;
        while(i < m  && b[i] == 1) cnt++,i++;
        for(auto x : di){
            mb[x]+=(cnt-x+1>0?cnt-x+1:0);
        }
    } 
    int ans = 0 ;
    for(auto it : res){
      //  cout<<it[0]<<" "<<ma[it[0]]<<ln;
      //  cout<<it[1]<<" "<<mb[it[1]]<<ln;
        ans+=ma[it[0]]*mb[it[1]];
        if(it[0] != it[1]) ans+=mb[it[0]]*ma[it[1]];
    }
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}