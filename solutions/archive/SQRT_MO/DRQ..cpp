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


// https://cses.fi/problemset/task/1648 
void solve(int test_case){
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    int SQ = sqrt(n) + 1;
    int blocks[SQ]{};
    for(int i = 0 ; i < n ; i++){
        blocks[i/SQ] += v[i];
    }
    while(q--){
        int op,a,b; cin>>op>>a>>b;
        if(op == 1){
            a--; 
            blocks[a/SQ]-= v[a];
            v[a] = b;
            blocks[a/SQ] += v[a];
        }
        else{
            int sum = 0; a--,b--;
            for(int i = (a/SQ)+1 ; i < (b/SQ) ; i++){
                sum += blocks[i];
            }
            for(int i = a ; i < (a/SQ + 1) * SQ && i <= b ; i++){
                sum += v[i];
            }
            for(int i = (b/SQ) * SQ ; i > a && i <= b ; i++){
                sum += v[i];
            }
            cout << sum << ln;
        }
    }   
}