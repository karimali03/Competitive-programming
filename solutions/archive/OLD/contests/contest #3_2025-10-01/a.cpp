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

const int N = 200005;
int dp[N][3][2][4];
int vis[N][3][2][4]{};
int c = 0;
// 0 0 0 0 0 1 1 1 1 1 2 2 2 2 2 
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;   c++;
    function<int(int,int,int,int)> rec=[&](int i,int st,int take,int len) ->int{
        if(i == n) return (st == 2 && len == 3 && take) ? 0 : -1e15;
        int &ret = dp[i][st][take][len];
        if(vis[i][st][take][len] == c) return ret;
        if(st == 0) ret = max(rec(i+1,st,take,len),rec(i+1,st+1,take,1) + i+1 + v[i]);
        else if(st == 1){
            ret = rec(i+1,st,take,min(3ll,len+1));
            if(!take) ret = max(ret , v[i] + rec(i+1,st,1,min(3ll,len+1)));
            if(len >= 2) ret = max(ret , v[i] - i - 1 + rec(i+1,st+1,take,3));
        } 
        else ret = rec(i+1,st,take,len);
        vis[i][st][take][len] = c;

        return ret;
    };
    cout<<max(rec(0,0,0,0),rec(1,1,0,1)+1+v[0])<<ln;
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