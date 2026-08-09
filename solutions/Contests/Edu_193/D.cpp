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
struct dsu {
    vector<int> size, par;
    int cc;

    dsu(int n) :size(n, 1), par(n),cc(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

};
void solve(int test_case) {
    int n,m; cin>>n>>m;
    dsu st(n+1);
    vii rh(11,vi(n+1));
    for(int i = 0;i < m; i++){
        int a,d,k; cin>>a>>d>>k;
        rh[d][a] = max(rh[d][a] , a + k*d);
      //  cout<<d<<" "<<a<<" "<<rh[d][a]<<endl;
    }   
    for(int d = 1 ; d <= 10 ; d++){
        for(int i = 1 ; i <= n ; i++){
            if(i-d >= 0) rh[d][i] = max(rh[d][i] , rh[d][i-d]);
            if(rh[d][i] > i) st.merge(i,i+d);
        }
    }

    cout<<st.cc-1<<ln;
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