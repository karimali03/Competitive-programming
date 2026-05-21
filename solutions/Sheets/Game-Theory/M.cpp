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

map<int,int>dp;
vector<int>opt;
int get(int x){
    if(x == 0) return 0;
    if(dp.count(x)) return dp[x];
    set<int>st;
    for(auto &it : opt){
        if(x%it == 0){
            if(it&1) st.insert(get(x/it));
            else st.insert(0);
        }
    }
    int mex = 0;
    while(st.count(mex)) mex++;
    return dp[x] = mex;
}

void solve(int test_case) {
    int n,m; cin>>n>>m;
    opt = vi(m); cin>>opt;
    if(get(n)) cout<<"First\n";
    else cout<<"Second\n";
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