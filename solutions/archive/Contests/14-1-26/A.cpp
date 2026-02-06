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
    map<char,char>id;
    id['a'] = id['b'] = id['c'] = '2';
    id['d'] = id['e'] = id['f'] = '3';
    id['g'] = id['h'] = id['i'] = '4';
    id['j'] = id['k'] = id['l'] = '5';
    id['m'] = id['n'] = id['o'] = '6';
    id['p'] = id['q'] = id['r'] = id['s'] = '7';
    id['t'] = id['u'] = id['v'] = '8';
    id['w'] = id['x'] = id['y'] = id['z'] = '9';
    set<string>st;
    for(int i = 0;i < n; i++){
        string s; cin>>s;
        string cur(7,'0');
        for(int x = 0; x < 7 ; x++){
            cur[x] = id[s[x]];
        }
        st.insert(cur);
    }
    cout<<(int)st.size()<<ln;

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