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
    string s; cin>>s;
    vii idx(10);
    int k; cin>>k;
    int n = s.size();
    int x = n - k;
    string res;
    for(int i = 0 ; i < n ; i++) idx[s[i]-'0'].push_back(i); 
    int cur = 0;
    for(int i = 0 ; i < x ; i++){
        for(int ch = 0 ; ch <= 9; ch++){
            if(ch == 0 && !i) continue;
            auto it = lower_bound(all(idx[ch]),cur);
            if(it == idx[ch].end() || n - *it - 1 < x - i - 1) continue;
            res.push_back((char)(ch + '0')); cur = *it+1;
            break;
        }
    }

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