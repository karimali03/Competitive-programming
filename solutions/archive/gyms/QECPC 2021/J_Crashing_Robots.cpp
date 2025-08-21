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
    vec<pair<int,int>> v(n);
    vec<string>x(n);
    vec<bool>stuck(n,false);
    int mx = 0;
  
    map<pair<int,int>,int> mp;
    f(i,0,n) cin>>x[i],mx=max<ll>(mx,x[i].size());
    f(i,0,n){
        cin>>v[i].first>>v[i].second;
        mp[v[i]]++;
    }
    vec<int>rem;
    f(i,0,n) rem.push_back(i);
    for(int i = 0 ; i < mx ; i++){
        for(auto j : rem){
            if(i >= x[j].size()) continue;
            mp[v[j]]--;
            if(x[j][i] == 'L') v[j].first--;
            else if(x[j][i] == 'R') v[j].first++;
            else if(x[j][i] == 'U') v[j].second++;
            else v[j].second--;
            mp[v[j]]++;
        }
        for(auto j : rem){
            if(mp[v[j]] > 1) stuck[j] = true;
        }
        for(int a = 0 ; a < rem.size() ; ){
            if(stuck[rem[a]]){
                swap(rem[a],rem.back());
                rem.pop_back();
            }
            else a++;
        }

    }
    int cnt = count(all(stuck),true);
    cout<<cnt<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
   freopen("robots.in", "r", stdin);  // Redirects standard input to read from "input.txt"
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}