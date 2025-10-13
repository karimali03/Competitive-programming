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


int MSB(int x){
    ll msb = 0;
    while (x){
        x >>= 1;
        msb++;
    }
    return msb - 1;
}


void solve(int test_case) {
    int n,q; cin>>n>>q;
    vi v(n); cin>>v;
    vii pre(n,vi(3));
    for(int i = 0 ; i < n ; i++){
        pre[i][0] = MSB(v[i]);
        if(co(v[i]) != 1 && co(v[i]-1) == 1) pre[i][1]++;
        else if(co(v[i]) != 1) pre[i][2]++;
        if(i) f(j,0,3) pre[i][j]+=pre[i-1][j]; 
    }
    auto calc = [&](int l,int r){
        auto ret = pre[r];
        if(l){
            f(i,0,3) ret[i]-=pre[l-1][i];
        }
        return ret;
    };

    while(q--){
        int l,r; cin>>l>>r;
        auto ret = calc(l-1,r-1);
        int res = ret[0] + ret[2] + ret[1]/2;
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