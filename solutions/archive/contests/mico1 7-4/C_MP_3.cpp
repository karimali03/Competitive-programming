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
    int n,s; cin>>n>>s;
    vi v(n); cin>>v; 
    set<int>st(all(v));
    if( (8*s) >= (ceil(log2((st.size()))) * n ) ) return void(cout<<0<<ln);

    int cnt = 0;
    map<int,int>mp;
    f(i,0,n) mp[v[i]]++;
    vi x;
    for(auto [a,b] : mp) x.push_back(b);
    vi pre(x.size());
    vi suf(x.size());
    f(i,0,x.size()){
        pre[i] = x[i] + (i?pre[i-1]:0);
    }
    for(int i = (int)x.size()-1 ; i >= 0 ; i--)
    suf[i] = x[i] + ((i!=(int)st.size()-1)?suf[i+1]:0);
    reverse(all(suf));
    int rm = (int)st.size() - pow(2 , (8*s) / n);
    int ans = n;
    for(int i  = 0 ;  i <= min((int)st.size()-2,rm) ; i++){
        int e = (i ? pre[i-1] : 0);
        if(rm-i) e+=suf[rm-i-1];
        ans = min(ans,e);
    }

    cout<<ans<<ln;
}