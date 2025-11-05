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

// Count how many times each prefix occurs as a substring
vi prefix_substr(string &s){ 
    int n = s.size();
    vi ret(n+1);
    auto pi = prefix_function(s);
    for(int i=0;i<n;i++) ret[pi[i]]++;
    for(int i=n-1;i>0;i--) ret[pi[i-1]] += ret[i];
    for(int i=0;i<=n;i++) ret[i]++;
    return ret;
}


void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    auto pi = prefix_function(s);
    vi ret(n+1);
    for(int i=0;i<n;i++) ret[pi[i]]++;
    for(int i=n-1;i>0;i--) ret[pi[i-1]] += ret[i];
    for(int i=0;i<=n;i++) ret[i]++;
    vii res;
    res.push_back({n,1});
    int j = pi[n-1];
    while(j>0){
        res.push_back({j,ret[j]});
        j = pi[j-1];
    }
    reverse(all(res));
    cout<<res.size()<<ln;
    for(auto &it : res) cout<<it[0]<<" "<<it[1]<<ln;
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