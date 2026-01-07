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
const int K = 55;
ld dp[K][N]{};
int v[N];
int n,k;

vector<ld> S(N, 0.0);   // S[i] = sum(t[1]...t[i])
vector<ld> IS(N, 0.0);  // IS[i] = sum(1/t[1]...1/t[i])
vector<ld> TIS(N, 0.0); // TIS[i] = sum(t[k] * IS[k-1] for k=1...i)

void precompute() {
    // S[0], IS[0], TIS[0] are already 0.0
    for (int i = 1; i <= n; ++i) {
        S[i] = S[i - 1] + v[i];
        IS[i] = IS[i - 1] + (1.0 / v[i]);
        // TIS[i] calculation uses IS[i-1] as derived in the formula
        TIS[i] = TIS[i - 1] + (v[i] * IS[i - 1]);
    }
}

ld C(int i,int j){
    return IS[j] * (S[j] - S[i - 1]) - (TIS[j] - TIS[i - 1]);
    double res = 1.0;
    int sum = v[i];
    for(int x = i+1 ; x <= j ; x++){
        sum += v[x];
        res += (sum*1.0)/v[x];
    }
    return res;
}
void calc(int cur,int l,int r,int optl,int optr){
    if(l>r) return;
    int mid = l + (r-l)/2;
    int kr = min(mid,optr);
  
    pair<ld,int> ans = {1e9,1e9};
    for(int x = optl ; x <= kr ; x++){
        ans = min(ans , {(x ? dp[cur-1][x-1] : 0.0) + C(x+1,mid+1) ,x});
    }
    dp[cur][mid] = ans.first;
    int opt = ans.second;
    calc(cur,l,mid-1,optl,opt);
    calc(cur,mid+1,r,opt,optr);
}
void solve(int test_case) {
    cin>>n>>k;
    f(i,0,n) cin>>v[i+1];
    precompute();
    for(int i = 0;i < n ; i++){
        dp[0][i] = C(1,i+1);
    }
    for(int x = 1 ; x < k ; x++){
        calc(x,0,n-1,0,n-1);
    }
    cout<<fixed<<setprecision(6)<<dp[k-1][n-1]<<ln;
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