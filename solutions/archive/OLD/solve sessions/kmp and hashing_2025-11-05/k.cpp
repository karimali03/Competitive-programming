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

const int MOD = 1e9+7;
vi prefix(string &s){
    int n = s.size();
    vi pi(n);
    for(int i = 1; i < n ; i++){
        int j = pi[i-1];
        while(j>0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
const int N = 205;
int dp[N][N][N][2];
void solve(int test_case) {
    int n; cin>>n;
    n*=2;
    string s; cin>>s; s.push_back('#');
    int sz = s.size();
    auto pi = prefix(s);
    vii aut(sz,vi(2));
    aut[0][(s[0] == '(' ? 0 : 1)] = 1;
    for(int i = 1;i < sz ; i++){
        for(int ch = 0 ; ch < 2 ; ch++){
            if((ch == 0 && s[i] == '(') || (ch == 1 && s[i] == ')')) aut[i][ch] = i+1;
            else aut[i][ch] = aut[pi[i-1]][ch];
        }
    }

    memset(dp,-1,sizeof(dp));
    function<int(int,int,int,int)> rec = [&](int i,int x,int j,int used) -> int{
        if(i > n || x > n || x < 0) return 0;
        if(i == n) return (x == 0 && used);
        int &ret = dp[i][x][j][used];
        if(~ret) return ret;
        ret = 0;
        // (
        int nj = aut[j][0];
        (ret += rec(i+1,x+1,nj,used|(nj == sz-1)))%=MOD;
        // )
        nj = aut[j][1];
        (ret += rec(i+1,x-1,nj,used|(nj == sz-1)))%=MOD;
        return ret;
    };
    cout<<rec(0,0,0,0)<<ln; 
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