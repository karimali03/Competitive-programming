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

#define bob cout<<"Bob"<<ln
#define alice cout<<"Alice"<<ln

void solve(int test_case){
    int n; cin>>n;
    set<int>a,b;
    string s; cin>>s;
    for(int i = 0 ; i < n ; i++){
        if(s[i] == 'A') a.insert(i+1);
        else b.insert(i+1);
    }   
    if(n == 2){
        if(a.count(1)) alice;
        else bob;
        return;
    }
    if(a.size() == 1 && a.count(1)) bob;
    else if(a.size() == 1 && a.count(n)) bob;
    else if(b.size() == 1 && b.count(1)) alice;
    else if(b.size() == 1 && b.count(n)) alice;
    else if(a.count(1) && a.count(n)) alice;
    else if(b.count(1) && b.count(n)) bob;
    else if(b.count(n) && *b.begin()>= 1 && *b.begin() < n) bob;
    else if(a.count(n) && a.count(n-1)) alice;
    else bob;
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