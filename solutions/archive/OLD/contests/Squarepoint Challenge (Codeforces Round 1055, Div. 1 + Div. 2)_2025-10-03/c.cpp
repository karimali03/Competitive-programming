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
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    vi pre(n);
    pre[0] = v[0];
    for(int i = 1 ; i < n ; i++) pre[i] = v[i] + pre[i-1];
    auto calc = [&](int l,int r) -> int{
        if(l > r) return 0;
        return pre[r] - (l ? pre[l-1] : 0);
    };
    vi pre2(n);
    for(int i = 0 ; i < n-1 ; i++){
        if(v[i] == v[i+1]) pre2[i]=1;
        if(i) pre2[i] += pre2[i-1];
    }
    auto calc2 = [&](int l,int r) -> int{
        if(l > r) return 0;
        return pre2[r] - (l ? pre2[l-1] : 0);
    };
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        int cnt = calc(l,r);
        if(cnt%3 || ((r-l+1)-cnt)%3){
            NA; continue;
        }
        int res = (r-l+1)/3;
        int eq = calc2(l,r-1);
      //  cout<<l<<" "<<r<<" "<<eq<<ln;
        if(!eq) res++;
        cout<<res<<ln;
    }
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