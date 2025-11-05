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
#define int ll
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



const int N = 4005;
const int K = 805;
int n,k;
int v[N][N];
int dp[K][N];
int pre[N][N];
const int INF = 1e9;


void init() {
    f(i,0,n+1) f(j,0,n+1) pre[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = v[i][j]
                      + pre[i][j - 1]
                      + pre[i - 1][j]
                      - pre[i - 1][j - 1];
        }
    }
}

int query(int from_x,int from_y,int to_x,int to_y) {
    from_x = max(1 , from_x); from_y = max(1 , from_y);
    to_x = min(n , to_x);  to_y = min( n , to_y);
    return pre[to_x][to_y] - pre[from_x - 1][to_y] 
           - pre[to_x][from_y-1] + pre[from_x-1][from_y-1]; 
}


int C(int x,int y){
    return query(x,x,y,y)/2;
}
void calc(int cur,int l,int r,int optl,int optr){
    if(l>r) return;
    int mid = l + (r-l)/2;
    int kr = min(mid,optr);
  
    pair<int,int> ans = {1e9,1e9};
    for(int x = optl ; x <= kr ; x++){
        ans = min(ans , {(x ? dp[cur-1][x-1] : 0) + C(x+1,mid+1) ,x});
    }
    dp[cur][mid] = ans.first;
    int opt = ans.second;
    calc(cur,l,mid-1,optl,opt);
    calc(cur,mid+1,r,opt,optr);
}

void solve(int test_case) {
    cin>>n>>k;
    f(i,0,n) f(j,0,n) cin>>v[i+1][j+1];
    f(i,0,K) f(j,0,N) dp[i][j] = INF;
    init();
    for(int i = 0; i <  n ; i++){
        dp[0][i] = C(1,i+1);
    }
    for(int x = 1 ; x < k ; x++) calc(x,0,n-1,0,n-1);
    cout<<dp[k-1][n-1]<<ln;
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