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


const int SQ = 460;
unordered_map<int, int> blocks[SQ];
void update(int i,int v , vi &a){
    blocks[i/SQ][a[i]]--;
    if(blocks[i/SQ][a[i]] == 0) blocks[i/SQ].erase(a[i]);
    a[i] = v;
    blocks[i/SQ][a[i]]++;
}
int query(int r, int x, vi &a){
    int ans= 0 ;
    for(int i = 0 ; i < r/SQ ; i++) {
        ans += blocks[i][x];
    }
    for(int i = (r/SQ)*SQ ; i < r ; i++){
        if(a[i] == x) ans++;
    }
    return ans;
}
int qu(int l,int r ,int x, vi &a){
    return query(r, x,a) - query(l-1, x,a);
}

// https://judge.yosupo.jp/problem/point_set_range_frequency
void solve(int test_case){
    int n, q; cin >> n >> q;
    vector<int> v(n); 
    for(int i = 0 ; i < n ; i++){
        cin >> v[i];
        blocks[i/SQ][v[i]]++;
    }
    while (q--) {
        int op; cin>>op;
        if (op == 0) {
            int a,b; cin>>a>>b;
            update(a, b,v);           
        } else {
            int a, b, x; cin >> a >> b >> x;
            cout << qu(a, b, x , v) << ln;
        }
    }
}