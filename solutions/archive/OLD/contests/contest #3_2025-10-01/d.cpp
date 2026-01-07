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


const int N = 505;
int v[N][N];
int pre[N][N];
int n,m,k; 

void init() {
    f(i,0,n+1) f(j,0,m+1) pre[i][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = v[i][j] 
                      + pre[i][j - 1]
                      + pre[i - 1][j]
                      - pre[i - 1][j - 1];
        }
    }
}

int query(int from_x,int from_y,int to_x,int to_y) {
    from_x = max(1ll , from_x); from_y = max(1ll , from_y);
    to_x = min(n , to_x);  to_y = min( m , to_y);
    return pre[to_x][to_y] - pre[from_x - 1][to_y] 
           - pre[to_x][from_y-1] + pre[from_x-1][from_y-1]; 
}

void solve(int test_case) {
    cin>>n>>m>>k;
    vii a(n,vi(m));
    for(int i = 0 ; i < n;  i++) cin>>a[i];
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            char c; cin>>c;
            v[i][j] = c-'0';
        }
    }
    init();
    int sum = 0;
    f(i,0,n) f(j,0,m) sum = sum + (v[i+1][j+1] ? a[i][j] : -a[i][j]);
  //  cout<<sum<<ln;
    if(sum == 0){
        YES; return;
    }
    int gc = 0;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            if(i+k <= n+1 && j+k <= m+1){
                int x = query(i,j,i+k-1,j+k-1);
                x = x - (k*k - x);
                gc = gcd(x,gc);
            }
        }
    }

    if(gc == 0) NO;
    else if((sum+gc)%gc == 0) YES;
    else NO;
 //   if(sum%gc == 0) YES;
 //   else NO;
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