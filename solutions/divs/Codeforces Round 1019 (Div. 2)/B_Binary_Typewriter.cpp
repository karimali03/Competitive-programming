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

void solve(int test_case){
    int n; cin>>n;
    string a; cin>>a;
    string s(n+1,'0');
    f(i,1,n+1) s[i] = a[i-1];
    int l = 0 , r = 0;
    s.push_back('1');
    for(int i = 1  ; i <= n ; i++){
        if( !l && s[i] == '1' && s[i-1] == '0'){
            l = i;
        }
        else if(l && !r && s[i] == '0' && s[i+1] == '1'){
            r = i;
        }
    }
    if(l && r) reverse(s.begin()+l,s.begin()+r+1);
    int c = 0;
    int res = 0;
 //   cout<<s<<ln;
    for(int i = 1 ; i <= n  ; i++){
        res++;
        if(s[i]-'0' != c) res++,c=1-c;
    }
    cout<<res<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}