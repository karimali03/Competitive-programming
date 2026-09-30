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


int calcLIS(vector<int> & v) { // O( n *  log(n) )
        int n = v.size();
        vector<int>bs(n+1,INT_MAX);
        vii idx(n+1);
        for(int i = 0 ;i < n ;i++){
            int x = lower_bound(bs.begin(),bs.begin()+i+1,v[i]) - bs.begin();
            bs[x] = v[i];
            idx[x].push_back(i);
        }
        return lower_bound(all(bs),INT_MAX)-bs.begin();
}

void solve(int test_case) {
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    int lis = calcLIS(v);
    k -= min(k , n-lis);
    lis -= k;
    cout<<lis<<ln;
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