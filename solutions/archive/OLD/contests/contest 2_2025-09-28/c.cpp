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

const int N = 200005;
int pre[N][26]{};
void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    pre[0][s[0]-'a']++;
    for(int i = 1 ; i < n ; i++){
        for(int x = 0 ; x < 26 ; x++) pre[i][x] = pre[i-1][x];
        pre[i][s[i]-'a']++;
    }
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        int cnt = 0;
        for(int i = 0 ; i < 26 ; i++){
            int x = pre[r][i] - (l ? pre[l-1][i]:0);
            if(x) cnt++;
        }
        bool vld = (l == r) || (cnt == 2 && s[l] != s[r]) || (cnt > 2);
        if( vld ) YES;
        else NO;
    }
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