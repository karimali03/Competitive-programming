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
    int n,c; cin>>n>>c;
    vii v(n);
    for(int i = 0 ; i < n ; i++){
        int x; cin>>x;
        int l = i+1+x;
        int r = n-i+x;
        v[i] = {min(l,r),i,x};
    }
    sort(all(v));
    vi x(n);
    for(int i = 0 ; i < n ; i++){
        x[v[i][1]] = v[i][0] + (i?x[i-1]:0);
    }
    if(n == 1){
        if(v[0][1]+1+v[0][2] <= c) cout<<1<<ln;
        else cout<<0<<ln;
        return;
    }
    int res = 0;
    for(int i = 0 ; i < n ; i++){
        int val = v[i][1]+1+v[i][2];
        auto bs = lower_bound(all(x),c-val) - x.begin();
        if(bs != n && x[bs] < c-val) bs--;
        if(bs ==)
        int idx = bs - x.begin();
        if(idx < v[i][1]) res = max(res , idx + 1);
        else{
            bs = lower_bound(all(x),c+val);
            if(bs != x.end() && bs != x.begin() && *bs > c+val) bs = prev(bs);
            idx = bs - x.begin();
            res = max(res , idx);
        }
    }
    cout<<res<<ln;

}