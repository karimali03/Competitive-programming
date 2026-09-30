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
    vector<array<int,4>>v(n);
    for(int i = 0;i < n ; i++){
        for(int j=0;j<4;j++) cin>>v[i][j];
    }
    for(int len = n ; len >= 0 ; len--){
        int x = 1,y = len;
        for(int i = 0;i < n ; i++){
            if(y == 0) break;
            auto [l,r,a,b] = v[i];
            if(x >= l && x <= r) continue;
            if(y >= a && y <=b) continue;
            x++,y--;
        }
        if(y == 0){
            cout<<len<<ln; return;
        }
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