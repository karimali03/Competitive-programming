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

vi val {1,4,3,2};
int rec(int n,int x,int y){
    int pos = (x/(n/2))  * 2 + y/(n/2);
    if(n == 2) return val[pos];
    if(pos == 1) return 3*pow(n/2,2) + rec(n/2,x,y-n/2);
    else if(pos == 2) return 2*pow(n/2,2)  + rec(n/2,x-n/2,y);
    else if(pos == 3) return pow(n/2,2) + rec(n/2,x-n/2,y-n/2);
    return rec(n/2,x,y);
}

// 0 1 -> 2^(n/4)
// 1 
// 2 2^(n/2+1) -
// 3 2^(n/4+1) -> 2^(n/2)
int cur_i,cur_j;
void calc(int num , int n){
    if(n == 4){
        if(num == 2) cur_i++,cur_j++;
        else if(num == 3) cur_i++;
        else if(num == 4) cur_j++;
        return;
    }
    int l = sqrt(n)/2;
    if(num <= n/4) calc(num,n/4);
    else if(num <= n/2) cur_i+=l,cur_j+=l,calc(num-n/4,n/4);
    else if(num <= 3*n/4) calc(num-n/2,n/4),cur_i+=l;
    else calc(num-(3*n/4),n/4),cur_j+=l;
}
void solve(int test_case){
    int n,q; cin>>n>>q; n = pow(2,n);
   // cout<<rec(2,0,1)<<ln;
    while(q--){
        char a,b; cin>>a>>b;
        if(a == '-'){
            int x,y; cin>>x>>y; x--,y--;
            cout<<rec(n,x,y)<<ln;
        }
        else {
            int x; cin>>x;
            cur_i = cur_j = 0;
            calc(x,n*n);
            cout<<cur_i+1<<" "<<cur_j+1<<ln;
        }
    }   
}