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
    vi pre(n);
    map<int,vi>suf;
    int dif = 0;
    int res = 1e9;
    for(int i = 0 ;i < n ; i++){
        dif += (s[i] == 'a' ? 1 : -1);
        pre[i] = dif;
        if(dif == 0) res = min(res , n - i -1); 
    }
    if(dif == 0){
        cout<<0<<ln;
        return;
    }
    dif = 0;
    for(int i = n-1; i >= 0 ; i--){
        dif += (s[i] == 'a' ? 1 : -1);
        suf[dif].push_back(i);
        if(dif == 0) res = min(res , i);
    }
    for(auto &[a,b] : suf) reverse(all(b));
    for(int i = 0 ;i < n ; i++){
        int x = pre[i];
        if(suf.count(-x)){
            auto it = upper_bound(all(suf[-x]),i);
            if(it != suf[-x].end()) res = min(res , n - (i+1) - (n - *it));
        }
    }
    if(res == 1e9 || res == n) NA;
    else cout<<res<<ln;
    
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