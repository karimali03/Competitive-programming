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
    vi v(n); cin>>v;
    vector<pair<int,int>>rng(m);
    for(int i = 0; i < m ; i++){
        cin>>rng[i].first>>rng[i].second;
        rng[i].first--; rng[i].second--;
    } 
    vector<set<int>>st(n);
    for(int i = 0;i < m ; i++) st[rng[i].first].insert(rng[i].second);
    vi pre(n+1);
    auto move = [&](set<int>&A,set<int>&B){
        if(A.size() > B.size()) swap(A,B);
        for(auto &it : A) B.insert(it);
        A.clear();
    };
    for(int i = 0;i < m ; i++){
        while(!st[i].empty() && *st[i].begin() < i) st[i].erase(st[i].begin());
        if(st[i].empty()) continue;
        auto it = *st[i].begin(); st[i].erase(st[i].begin());
        pre[i] ^= 1; pre[it+1] ^= 1;
        // it+1
        move(st[i],st[it+1]);
    }
    for(int i = 1;i < n ; i++) pre[i] ^= pre[i-1];
    cout<<pre<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}