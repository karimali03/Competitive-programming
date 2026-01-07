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

void solve(int test_case) {
    int n; cin>>n;
    string s; cin>>s;
    int x = count(all(s),'1');
    if(x == n || x == 0){
        YES; return;
    }
    vi cnt;
    for(int i = 0 ; i < n ;){
        while(i < n && s[i] == '1') i++;
        int st = i;
        while (i < n && s[i] == '0') i++;
        if(i-st) cnt.push_back(i-st);
    }
    vii dp(n,vi(3,-1));
    function<int(int,int)> rec = [&](int i,int j) -> int{
       if(i == n) return (j == 0);
       int &ret = dp[i][j];
       if(~ret) return ret;
       ret = 0;
       if(s[i] == '0'){
         if(j == 1) ret = rec(i+1,0);
         else{
             if((i == 0 || s[i-1] == '0')) ret += rec(i+1,0);
             if(i+1 == n || s[i+1] == '0') ret += rec(i+1,0);
             else ret += rec(i+2,1);
         }
       }
       else if(j == 0) ret = rec(i+1,0);
       return ret;
    };
    if(rec(0,0)) YES;
    else NO;
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