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

int compute_mex(vector<int> &values) {
    int n = (values.size());
    vector<bool> seen(n + 1, false);
 
    for (const auto &x : values)
        if (x <= n)
            seen[x] = true;
 
    int mex = 0;
 
    while (seen[mex])
        mex++;
 
    return mex;
}

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vi cnt(n+1);
    f(i,0,n) cnt[v[i]]++;
    int mex = compute_mex(v);
    if(mex == k) cout<<0<<ln;
    else if(mex > k){
         cout<<cnt[k]<<ln;
    }
    else{
        int res = 0;
        for(int i = mex ; i < k ; i++) if(!cnt[i]) res++;
        int use = min(res , cnt[k]);
        res = res  + cnt[k] - use;
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