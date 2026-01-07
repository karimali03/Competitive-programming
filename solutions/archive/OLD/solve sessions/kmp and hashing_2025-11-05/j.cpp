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
    vi pi(n);
    for(int i = 1 ; i < n; i++){
        int j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vii dp;
string a,b;
int n,m;
vi pi;
int rec(int i,int j){
    if(i == n) return 0;
    int &ret = dp[i][j];
    if(~ret) return ret;
    ret = 0;
    if(a[i] == '?'){
        if(j == m) ret = rec(i,pi[j-1]);
        else ret = rec(i+1,j+1) + (j+1 == m);
        if(j == 0) ret = max(ret , rec(i+1, 0));
        else ret = max(ret , rec(i , pi[j-1]));
    }else{
        if(a[i] == b[j]) ret = rec(i+1,j+1) + (j+1 == m);
        else if(j == 0) ret = rec(i+1,0);
        else ret = rec(i,pi[j-1]);
    }
    return ret;
}
void solve(int test_case) {
    cin>>a>>b;
    string cur = b + '#';
    pi = prefix_function(cur);
    n = a.size();
    m = b.size();
    dp = vii(n,vi(m+1,-1));
    cout<<rec(0,pi[m])<<ln;
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