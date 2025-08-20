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

const int mod = 998244353;

struct FenwickTree {
    vector<int> bit;  
    int n;

    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    // Adds value 'val' at index 'idx' (0-based index)
    void update(int idx, int val) {
        idx++;  // Convert to 1-based index
        while (idx <= n) {
            bit[idx] = (bit[idx]%mod +  val%mod)%mod;
            idx += idx & -idx;
        }
    }

    // Returns the prefix sum from 0 to idx (0-based index)
    int query(int idx) {
        idx++;  // Convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum =  (sum%mod + bit[idx]%mod)%mod;
            idx -= idx & -idx;
        }
        return sum;
    }

    // Returns the range sum [l, r] (0-based indices)
    int range_query(int l, int r) {
        return (query(r)%mod + mod - query(l - 1)%mod)%mod;
    }
};


void solve(int test_case){
    int n,k; cin>>n>>k;
    vii v(k,vi(2));
    f(i,0,k){
        cin>>v[i][0]>>v[i][1];
    }   
    FenwickTree fnk(n+5);
    fnk.update(1,1);
    for(int i = 2 ; i <= n ; i++) {
        int sum = 0;
        for(auto x : v){
            int r = max(0ll,i-x[0]);
            int l = max(0ll,i-x[1]);
            sum = (sum%mod + fnk.range_query(l,r)%mod)%mod;
        }
        fnk.update(i,sum);
    }
    cout<<ln;

    cout<<fnk.range_query(n,n)<<ln;

}