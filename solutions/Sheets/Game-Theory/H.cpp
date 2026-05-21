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

const int N = 1000005;
int grundy[N];
int calc(int n){
    if(n == 1) return 0;
    int &ret = grundy[n];
    if(~ret) return ret;
    set<int>st;
    for(int i=1;i*i<=n;i++){
        if(n%i!=0) continue;
        int a = i , b = n/i;
        if((a&1) && b != n) st.insert(calc(b));
        else st.insert(0);
        if((b&1) && a != n) st.insert(calc(a));
        else st.insert(0);
    }
    int res = 0;
    while(st.count(res)) res++;
    return ret = res;
}
void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    int xr = 0;
    for(auto &it : v){
        xr ^= calc(it);
    }
    if(xr) cout<<1<<ln;
    else cout<<2<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(grundy,-1,sizeof grundy);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}