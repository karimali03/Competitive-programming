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
    int n; cin>>n;
    vi v(n); cin>>v;
    f(i,1,n) v[i] += v[i-1];
    int q; cin>>q;
    auto summ = [](int n){
        return n*(n+1)/2;
    };
    auto rng = [&](int x,int y){
        if(y < x) return 0ll;
        return summ(y) - summ(x-1);
    };
    auto calc = [&](int l,int r,int u){
        int sum = v[r];
        if(l) sum -= v[l-1];
        int use = min(u , sum);
        int res = rng(u-use+1,u);
        sum -= use+1;
        res -= rng(1,sum);
        return res;
    };
    while(q--){
        int l,u; cin>>l>>u; l--;
        if(l) u += v[l-1];
        auto it = upper_bound(all(v),u) - v.begin();
        auto it2 = it-1;
        if(l) u -= v[l-1];
       // cout<<l<<" "<<it<<" "<<it2<<ln;
        int mx = -1 , idx = -1;
        if(it < n) mx = calc(l,it,u) , idx = it;
        if(it2 >= l && calc(l,it2,u) >= mx) idx = it2;
        cout<<idx+1<<" ";
    }
    cout<<ln;
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