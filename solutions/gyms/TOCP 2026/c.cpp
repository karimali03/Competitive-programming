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
    int n,m; cin>>n>>m;
    vector<array<int,3>>v(m);
    f(i,0,m) cin>>v[i][0]>>v[i][1]>>v[i][2];
    vi dist(n+1);
    if(m)
    dist[v[m-1][0]] = dist[v[m-1][1]] = v[m-1][2];
    for(int i = m-2 ; i >= 0 ; i--){
        int d1 = dist[v[i][0]] , d2 = dist[v[i][1]];
        dist[v[i][0]] = d2 + v[i][2];
        dist[v[i][1]] = d1 + v[i][2]; 
    }
    cout<<*max_element(all(dist))<<ln;
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