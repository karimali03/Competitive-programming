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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());




void solve(int test_case) {
    int n,q; cin>>n>>q;
    map<int,vi>mp;
    vector<int>v(n); cin>>v;
    f(i,0,n) mp[v[i]].push_back(i);
    for(int i = 0 ; i < q ; i++){
        int l,r; cin>>l>>r; l--,r--;
        vi res;
        for(int i = 0 ; i < 200 ; i++){
              int rnd = v[l + rng()%(r-l+1)];
              int frq = upper_bound(all(mp[rnd]),r) - lower_bound(all(mp[rnd]),l);
              if(frq > (r-l+1)/3) res.push_back(rnd);
        }
        sort(all(res));
        res.erase(unique(all(res)), res.end());
        if(res.empty()) cout<<-1<<ln;
        else{
            for(auto it : res) cout<<it<<" ";
            cout<<ln;
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