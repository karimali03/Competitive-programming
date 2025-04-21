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
    vi a(n),b(n); cin>>a>>b;
    int cnt = 0;   
    map<pair<int,int>,int>mp;
    for(int i = 0 ; i <  n ; i++){
        if(!a[i] && !b[i]) cnt++;
        else if(!b[i]) mp[{0,1}]++;
        else if(!a[i]) continue;
        else{
            int x = b[i]/gcd(a[i],b[i]);
            int y = a[i]/gcd(a[i],b[i]);
            if(x*y < 0){
                if(x > 0) x*=-1,y=abs(y);
            }
            if(x < 0 && y < 0) x=-x,y=-y;
            mp[{x,y}]++;
        }
    }
    int mx = 0;
    for(auto [x,y] : mp) mx = max(mx,y);
    cout<<cnt+mx<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}