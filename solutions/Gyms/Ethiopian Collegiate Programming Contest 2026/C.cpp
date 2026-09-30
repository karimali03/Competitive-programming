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
    string s; cin>>s;
    if(n == 1){
        cout<<1<<ln; return;
    }
    vi cnt(10);
    for(auto &it : s) cnt[it-'0']++;
    int res = 1;
    if(s[0] == '0'){
        int sm = 0;
        for(int i=1;i<10;i++) sm+=cnt[i];
        cout<<sm<<ln; return;
    }
    int sm = 0;
    for(int i=1;i<10;i++){
        res += (sm * cnt[i]);
        sm += cnt[i];
    }
    if(sm) res += (sm-1)*(cnt[0]);
    cout<<res<<ln;

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