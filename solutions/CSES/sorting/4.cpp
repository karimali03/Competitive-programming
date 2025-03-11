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




void kemo() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
}



void solve(int test_case);

signed main() {
    kemo();
 
    int t = 1;
   // cin >> t;

    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}




void solve(int test_case){
	int n,m; cin>>n>>m;
    vi a(n),b(m);
    for(int i = 0 ; i < n ; i++) cin>>a[i];
    for(int j = 0 ; j < m ; j++) cin>>b[j];
    multiset<int>st(a.begin(),a.end());
    for(int i = 0 ; i < m ; i++){
        if(!st.empty()){
            auto bs = st.lower_bound(b[i]);
            if(bs == st.end()){
                bs = prev(bs);
                cout<<*bs<<ln;
                st.erase(bs);
            }
            else if(*bs > b[i]){
                if(bs == st.begin()) cout<<-1<<ln;
                else{
                    bs=  prev(bs);
                    cout<<*bs<<ln;
                st.erase(bs);
                }
            }
            else{
                cout<<*bs<<ln;
                st.erase(bs);
            }

        }
        else cout<<-1<<ln;
    }
}
