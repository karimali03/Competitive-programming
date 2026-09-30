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
    bool fz = (s[0] == '0') , ez = (s[n-1] == '0');
    vi cur;
    for(int i = 0;i < n ; ){
        auto ch = s[i]; int cnt = 0;
        while(i < n && s[i] == ch){
            cnt++; i++;
        }
        cur.push_back(cnt);
    }
    vi c(2);
    int st = (fz ? 0 : 1);
    for(auto &it : cur){
        c[st] += (it-1);
        st ^= 1;
    }
    if(abs(c[0]-c[1]) <= 1){
        cout<<c[0]+c[1]<<ln; return;
    }
    if(c[0] < c[1] && abs(c[0]-c[1]) > 1 && fz) c[0]++;
    else if(c[1] < c[0] && abs(c[0]-c[1]) > 1 && !fz) c[1]++;
    if(c[0] < c[1] && abs(c[0]-c[1]) > 1 && ez) c[0]++;
    else if(c[1] < c[0] && abs(c[0]-c[1]) > 1 && !ez) c[1]++;
    if(abs(c[0]-c[1]) <= 1){
         cout<<c[0]+c[1]<<ln; return;
    }
    NA;
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