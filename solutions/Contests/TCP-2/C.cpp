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
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vi vld(n);
    int sum = 0;
    int st = (-k + n)%n;
    int cnt = 2*k+1;
    while(cnt--){
        sum += v[st];
        st = (st+1)%n;
    }
    if(v[0] >= (sum + 2*k) / (2*k+1)) vld[0] = 1;
    for(int i = 1 ;i < n ; i++){
        int prv = (i - k - 1 + n)%n;
        sum -= v[prv]; 
        int nxt = (i + k)%n;
        sum += v[nxt];
        if(v[i] >= (sum + 2*k) / (2*k+1) ) vld[i] = 1;
    }
    st = (-k+n)%n;
    sum = 0; cnt = 2*k+1;
    while(cnt--){
        sum += vld[st];
        st = (st+1)%n;
    }
    int res = 0;
    if(vld[0]) res += v[0]*(2*k+1-sum);
    else res -= v[0]*sum;
    for(int i = 1; i < n ; i++){
        int prv = (i - k - 1 + n)%n;
        sum -= vld[prv]; 
        int nxt = (i + k)%n;
        sum += vld[nxt];
        int x = 2*k+1 - sum;
        if(vld[i]) res += v[i]*x;
        else res -= v[i]*sum;  
    }
    cout<<res<<ln;
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