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

const int N = 17;
string s; 
int n;
int mx;
ll dp[81][17][17][17][17][17];
int vis[81][17][17][17][17][17]{};
int val[10][17]{};
int cnt = 1;
int rec(int i,int a,int b,int c,int d,int e){
    if(i == n) return 0;
    ll &ret = dp[i][a][b][c][d][e];
    if(vis[i][a][b][c][d][e] == cnt) return ret;
    ret = 0;
    if(a == 0){
        ret = val[s[i]-'0'][a] + rec(i+1,a+1,b,c,d,e);
    }else if(b == 0){
        if(a != mx)  ret = val[s[i]-'0'][a] + rec(i+1,a+1,b,c,d,e);
        ret = max(ret , val[s[i]-'0'][b] + rec(i+1,a,b+1,c,d,e) );
    }else if(c == 0){
        if(a != mx)  ret = val[s[i]-'0'][a] + rec(i+1,a+1,b,c,d,e);
        if(b != mx) ret = max(ret , val[s[i]-'0'][b] + rec(i+1,a,b+1,c,d,e) );
        ret = max(ret , val[s[i]-'0'][c] + rec(i+1,a,b,c+1,d,e) );
    }else if(d == 0){
        if(a != mx)  ret = val[s[i]-'0'][a] + rec(i+1,a+1,b,c,d,e);
        if(b != mx) ret = max(ret , val[s[i]-'0'][b] + rec(i+1,a,b+1,c,d,e) );
        if(c != mx) ret = max(ret , val[s[i]-'0'][c] + rec(i+1,a,b,c+1,d,e) );
        ret = max(ret , val[s[i]-'0'][d] + rec(i+1,a,b,c,d+1,e) );
    }else{
        if(a != mx)  ret = val[s[i]-'0'][a] + rec(i+1,a+1,b,c,d,e);
        if(b != mx) ret = max(ret , val[s[i]-'0'][b] + rec(i+1,a,b+1,c,d,e) );
        if(c != mx) ret = max(ret , val[s[i]-'0'][c] + rec(i+1,a,b,c+1,d,e) );
        if(d != mx) ret = max(ret , val[s[i]-'0'][d] + rec(i+1,a,b,c,d+1,e) );
        if(e != mx) ret = max(ret , val[s[i]-'0'][e] + rec(i+1,a,b,c,d,e+1) );
    }
    return ret;
}
string res;
void build(int i,int a,int b,int c,int d,int e){
    if(i == n) return;
    ll &ret = dp[i][a][b][c][d][e];
    if(a != mx && rec(i+1,a+1,b,c,d,e) + val[s[i]-'0'][a] == ret){
        res.push_back('A');
        build(i+1,a+1,b,c,d,e);
        return;
    }else if(b != mx && rec(i+1,a,b+1,c,d,e) + val[s[i]-'0'][b] == ret){
        res.push_back('C');
        return;
    }else if(b != mx && rec(i+1,a,b+1,c,d,e) + val[s[i]-'0'][b] == ret){
        
    }else if(b != mx && rec(i+1,a,b+1,c,d,e) + val[s[i]-'0'][b] == ret){
        
    }else if(b != mx && rec(i+1,a,b+1,c,d,e) + val[s[i]-'0'][b] == ret){
        
    }else if(b != mx && rec(i+1,a,b+1,c,d,e) + val[s[i]-'0'][b] == ret){
        
    }
}

void solve(int test_case) {
    cin>>n;
    cin>>s;
    mx = n/5;
    cout<<rec(0,0,0,0,0,0)<<ln;
    cnt++;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for(int i = 0 ; i < 10 ; i++){
        val[i][0] = i;
        for(int j = 1 ; j < 17 ; j++) val[i][j] = i * val[i][j-1];
    }
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}