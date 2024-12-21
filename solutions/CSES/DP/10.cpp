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

// Overload for set
template<typename T = int>
ostream &operator<<(ostream &out, const set<T> &s) {
    for (const T &x : s) out << x << ' ';
    return out;
}

// Overload for map
template<typename K = int, typename V = int>
ostream &operator<<(ostream &out, const map<K, V> &m) { 
    for (const auto &[key, value] : m) out << '(' << key << ": " << value << ") ";
    return out;
}

// Overload for pair
template<typename A = int, typename B = int>
ostream &operator<<(ostream &out, const pair<A, B> &p) {
    return out << p.first << ", " << p.second;
}



void kemo() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
}



void solve(int test_case);

signed main() {
    kemo();
 
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}




int dp[5001][5001];
string a,b;
int rec(int i,int j){
    if(i == a.size()) return b.size()-j;
    if(j == b.size()) return a.size()-i;
    int &ret = dp[i][j];
    assert(ret!=-1);
    return ret;
}
void solve(int test_case) {
    cin>>a>>b;
    memset(dp,-1,sizeof(dp));
    for(int i = a.size()-1 ; i >= 0 ; i--){
        for(int j = b.size()-1 ; j >= 0 ; j--){
            int &ret = dp[i][j];
            if(a[i] == b[j]) ret = rec(i+1,j+1);
            else {
                int ch1 = 1 + rec(i+1,j);
                int ch2 = 1 + rec(i+1,j+1);
                int ch3 = 1 + rec(i,j+1);
                ret = min({ch1,ch2,ch3});
            }
        }
    }
    cout<<rec(0,0)<<"\n";
}
