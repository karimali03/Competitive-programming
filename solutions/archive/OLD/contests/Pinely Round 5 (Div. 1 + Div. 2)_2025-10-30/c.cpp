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
    vii idx(n+1);
    f(i,0,n) idx[v[i]].push_back(i);
    sort(all(v));
    v.erase(unique(all(v)),v.end());
    int sz = v.size();
    function<int(int,int,int)> rec = [&](int i,int l,int r) -> int{
        if(i >= sz) return 0;
        if(i == sz-1) return upper_bound(all(idx[v[i]]),r) - lower_bound(all(idx[v[i]]),l);
        int ret = upper_bound(all(idx[v[i]]),r) - lower_bound(all(idx[v[i]]),l) + rec(i+2,l,r);
        ret = max(ret , rec(i+1,l,r));
        for(int x = l; x < r ; x++){
            int cur = rec(i+1,l,x) + upper_bound(all(idx[v[i]]),x+1) - lower_bound(all(idx[v[i]]),r);
            ret = max(ret , cur);
        }
        return ret;
    };

    cout<<n-rec(0,0,n-1)<<ln;
    
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