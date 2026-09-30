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
#define int ll
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

const int N = 3e5 + 5;
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    if(n == 1){
        YES; return;
    }
    set<int>A[2];
    for(int i = 0;i < n ; i++){
        if(i&1) A[1].insert(v[i]);
        else A[0].insert(v[i]);
    }
    viii dp(n+1,vii(2,vi(2,-1)));
    function<int(int,int,int)> rec = [&](int x,int l,int r) -> int{
        if(x == 0) return 1;
        int &ret = dp[x][l][r];
        if(~ret) return ret;
        int op1 = 0 , op2 = 0;
        if(A[l].count(x)) op1 = rec(x-1,1-l,r);
        if(A[r].count(x)) op2 = rec(x-1,l,1-r);
        return ret = max(op1,op2);
    };
    int X = (A[1].count(n));
    int res = rec(n-1 , 1 - X , 1 - X);
    if(res) YES;
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