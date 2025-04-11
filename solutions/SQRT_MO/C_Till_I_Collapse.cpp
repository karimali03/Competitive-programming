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
// #define int long long


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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
// find_by_order(k): Returns the k-th element (0-based index).
// order_of_key(value): Returns the count of elements strictly less than value.


void solve(int test_case);

int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

vi loc[200005];
vi stg[200005];
int res[200005]{};


void solve(int test_case){
    int n; cin>>n;
    vi v;
    for(int i = 0 ; i < n ; i++){
        int x; cin>>x; x--;
        if(v.empty() || x != v[i-1]) v.push_back(x);
    }
    int m = n;
    n = v.size();
  
    for(int i = 0 ; i < m ; i++){
        loc[i].push_back(n);
        stg[0].push_back(i);
    }
    for(int i = n-1 ; i >= 0 ; i--){
        loc[v[i]].push_back(i);
    }
    ordered_set st; st.insert(n);
    for(int i = 0 ;i < m ; i++){
        st.insert(loc[i].back());
    }
 

    for(int i = 0 ; i < n ; i++){
        for(auto x : stg[i]){
            res[x]++;
            int sz = st.size();
            stg[*st.find_by_order(min(x+1,sz-1))].push_back(x);
        }
    
        st.erase(loc[v[i]].back());
        loc[v[i]].pop_back();
        st.insert(loc[v[i]].back());
    }
    
    for(int i = 0 ; i < m ;i++) cout<<res[i]<<" ";

}