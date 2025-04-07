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
    vi a(n),b(n); cin>>a>>b;
    map<int,int>x,y;
    int cnt = 0;
    int nidx = -1;
    for(int i = 0 ; i < n ;i++){
        if(a[i] == b[i]) cnt++,nidx = i;
    }
    if((cnt > 1 && n&1) || (cnt && n%2==0))
    return void(cout<<-1<<ln);
    vi xx = a;
    reverse(all(xx));
    if(xx == b) return void(cout<<0<<ln);
    map<int,int> xr;
    map<int,int>vis;
    for(int i = 0 ; i < n ; i++){
        if(vis[b[i]]){
            if(xr[b[i]] != a[i]) return void(cout<<-1<<ln);
        }
        else{
            vis[a[i]] = 1;
            xr[a[i]] = b[i];
        }
        x[a[i]] = i;
        y[b[i]] = i;
    }   

    vii op;
    if(nidx != -1 && nidx != n/2){
        op.push_back({n/2 , nidx});
        swap(a[nidx],a[n/2]); swap(b[nidx],b[n/2]);
        x[a[nidx]] = nidx;
        y[b[nidx]] = nidx;
        x[a[n/2]] = n/2;
        y[b[n/2]] = n/2;
    }
    for(int i = 0  ; i < n/2 ; i++){
        if(n-i-1 == y[a[i]]) continue;
       op.push_back({n-i-1,y[a[i]]});
       int idx = y[a[i]];
       swap(a[n-i-1],a[idx]); swap(b[n-i-1],b[idx]);
       x[a[n-i-1]] = n-i-1;
       y[b[n-i-1]] = n-i-1;
       x[a[idx]] = idx;
       y[b[idx]] = idx;
    }
   
    cout<<op.size()<<ln;
    for(auto it : op){
        cout<<it[0]+1<<" "<<it[1]+1<<ln;
    }
  
}