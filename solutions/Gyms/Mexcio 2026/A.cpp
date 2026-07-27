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

const int M = 998244353;
void solve(int test_case) {
    int n,k; cin>>n>>k;
    string s; cin>>s;
    auto pi = prefix_function(s);
    vi opt;
    for(int i = 0 ; i < n ; i++){
        if(pi[i] == 0) opt.push_back(i+1);
    }    

    vi dp(k+1);
    dp[0] = 1;
    for(int i = 1 ; i <= k ; i++){
        for(auto &it : opt){
            if(it > i) break;
            (dp[i] += dp[i-it])%=M;
        }
    }
    cout<<dp[k]<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}