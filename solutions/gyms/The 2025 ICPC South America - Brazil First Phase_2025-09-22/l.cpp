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
    vi x(n),y(n);
    f(i,0,n) cin>>x[i]>>y[i];
    vector<pair<int,int>>rng(n);
    vi dist(n);
    for(int i = 0 ; i < n - 1 ; i++) dist[i] = abs(x[i]-x[i+1]) + abs(y[i]-y[i+1]);
    rng[n-1] = {1 , dist[n-2]-1};
    for(int i = n-2 ; i >= 0 ; i--){
        rng[i+1].first = max(rng[i+1].first , 1ll);
        rng[i+1].second = min(rng[i+1].second , dist[i]-1);
        rng[i].first = dist[i] - rng[i+1].second;
        rng[i].second = dist[i] - rng[i+1].first;
    }
  
    if(rng[0].first > rng[0].second) cout<<-1<<ln;
    else  cout<<rng[0].second<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
 
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}