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
    int sum = 0;
    int cc;

    dsu(int n) : cc(n), size(n, 1), par(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }
    int calc(int x){
        return x*(x-1)/2;
    }
    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        sum = sum - calc(size[x]) - calc(size[y]);
        size[y] += size[x];
        size[x] = 0;
        sum += calc(size[y]);
        cc--;
        return true;
    }

};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vector<array<int,3>>ed(n-1);
    for(int i = 0;i < n-1 ; i++){
        ed[i] = {abs(v[i]-v[i+1]),v[i]-1,v[i+1]-1};
    }
    sort(all(ed));
    dsu st(n);
    vi res(n-1);
    for(int d = n-1 ; d > 0 ; d--){
    //    cout<<d<<endl;
        while(!ed.empty() && ed.back()[0] >= d){
            auto [a,b,c] = ed.back();
            ed.pop_back();
            st.merge(b,c);
        }
        res[d-1] = st.sum;
    }
  //  cout<<".."<<endl;
    for(int i = 0;i < n-1 ; i++) cout<<res[i]<<" ";
    cout<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
     cin>>t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}