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
    int n,x; cin>>n>>x;
    vi a(n),b(n); cin>>a>>b;
    vi step(n);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>q;
    for(int i = 0;i < n ; i++){
        q.push({a[i] / b[i],i});
    }
    int cnt = 0;
    int res = 0;
    while(true){
        auto [v,id] = q.top(); q.pop();
        if(v < cnt) break;
        a[id] += x;
        q.push({a[id] / b[id],id});
        if(q.top().first < cnt+1) break;
        res++; cnt++;
        if(cnt > 1e6){
            NA; return;
        }
    }
    cout<<res<<ln;
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