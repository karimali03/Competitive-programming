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


pair<int,int> id[3][26];
int vld[5][5]{};
const int N = 100005;
int dp[N][3];
int n;
string s;
int rec(int i,int j){
    if(i == n) return 0;
    int &ret = dp[i][j];
    if(~ret) return ret;
    auto [x,y] = id[j][s[i]-'A'];
    if(vld[x][y]) return ret = 1e10;
    ret = min({rec(i+1,0)+j,rec(i+1,1)+abs(j-1),rec(i+1,2)+abs(j-2)});
    return ret;
}
void solve(int test_case) {
    vi cnt(4); cin>>cnt;
    f(j,0,5) f(k,0,5) vld[j][k] = 0;
    for(int i = 0;i < 4 ; i++){
        for(int x = 0; x < cnt[i] ; x++){
            vld[x][i] = 1;
        } 
    }
    cin>>s;
    n = s.size();
    f(i,0,n+1) f(j,0,3) dp[i][j] = -1;
    int ans = min({rec(0,1),1+rec(0,0),1+rec(0,2)});
    if(ans > 1e9) ans = -1;
    cout<<ans<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int ch = 0;
    for(int i = 0;i < 5 ; i++){
        for(int j = 0;j < 4 ; j++){
            id[1][ch++] = {i,j};
        }
    }
    ch = 0;
    for(int j = 3 ; j >= 0 ; j--){
        for(int i = 0 ;i < 5 ; i++){
            id[0][ch++] = {i,j};
        }
    }

    ch = 0;
    for(int j = 0 ; j < 4; j++){
        for(int i = 4 ; i >= 0 ; i--){
            id[2][ch++] = {i,j};
        }
    }

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
