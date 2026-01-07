#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

vector<int> prefix_function(string &s){
    int n = s.size();
    vector<int>pi(n);
    int j = 0;
    for(int i = 1;i < n ; i++){
        while(j > 0 && s[i] != s[j]) j = pi[j-1]; 
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

void solve(int test_case) {
    string s; cin>>s;
    auto pi = prefix_function(s);
    int n = s.size();
    vi cnt(n+1);
    for(int i = 1; i < n-1;i++) cnt[pi[i]]++;
    int j = pi[n-1];
    while(j > 0){
        if(cnt[j]){
            cout<<s.substr(0,j)<<ln;
            return;
        }
        j = pi[j-1];
    }
    cout<<"Just a legend\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
  
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}