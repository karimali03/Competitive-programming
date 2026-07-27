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
    int n,q; cin>>n>>q;
    vector<pair<int,int>>v(n);
    f(i,0,n) cin>>v[i].first>>v[i].second;
    vector<pair<int,int>>ev(n*2);
    f(i,0,n){
        ev[i] = { v[i].first , 1};
        ev[i+1] = {v[i].second + 1 , -(v[i].second-v[i].first)};
    }
    sort(all(ev));
    vector<pair<int,int>>qr;
    for(int i = 0;i < q ; i++){
        int x; cin>>x;
        qr[i] = {x , i};
    }
    int sum = 0;
    int x = 0;
    vi ans(q);
    sort(all(qr));
    for(int i = 0;i < q ; i++){
        while(sum < qr[i].first){
            
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